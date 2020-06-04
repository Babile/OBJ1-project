#include "GameManager.h"
#include "View.h"
#include "Mouse.h"
#include "Hero.h"
#include "Controller.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

const int LEFTMOUSEBTN = 0, RIGHTMOUSEBTN = 1;

View *printController;
Mouse* mouseController;
Controller* unitsController;
std::vector<BaseUnit*> units;

bool spondState = true;
bool safeRightButtonPress = false;

void saveGame();
void loadGame();

template <typename T>
std::string mumberToString(T Number) {
	std::ostringstream oss;
	oss << Number;
	return oss.str();
}

template <typename T>
T stringToNumber(const std::string &Text) {
	std::istringstream iss(Text);
	T result;
	return iss >> result ? result : 0;
}

GameManager::GameManager() {
	printController = new View();
	mouseController = new Mouse();
	unitsController = new Controller();
	this->gameRunning = true;
}

void GameManager::startAplication() {
	while (this->gameRunning) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			this->gameRunning = false;
		}
		else if (GetAsyncKeyState(VK_TAB) & 0x8000) {
			saveGame();
		}
		else if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			if (!units.empty()) {
				sort(units.begin(), units.end());
			}
		}
		else if (GetAsyncKeyState(VK_MENU) & 0x8000) {
			loadGame();
		}

		else {
			spondState = true;
			mouseController->calculateMousePositionAndClick();

			if (mouseController->getMouseState(LEFTMOUSEBTN).pressed) {
				if (mouseController->getMouseState(LEFTMOUSEBTN).hold) {
					printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), mouseController->getMouseState(LEFTMOUSEBTN).hold);
				}
				for (int i = 0; i < units.size(); i++) {
					if (mouseController->getMouseX() == units.at(i)->getCordX() && mouseController->getMouseY() == units.at(i)->getCordY()) {
						units.at(i)->setSelected(true);
					}
					else {
						units.at(i)->setSelected(false);
					}
				}
			}

			else if (mouseController->getMouseState(RIGHTMOUSEBTN).pressed) {
				for (int i = 0; i < units.size(); i++) {
					if (units.at(i)->getSelected()) {
						units.at(i)->setMoving(true);
						units.at(i)->setMoveCordX(mouseController->getMouseX());
						units.at(i)->setMoveCordY(mouseController->getMouseY());
						spondState = false;
					}
				}
				if (spondState) {
					units.push_back(new Hero(mouseController->getMouseX(), mouseController->getMouseY(), "Hero", 5500, 5));
					spondState = false;
				}
				/*if (spondState) {
					if (units.size() == 0) {
						
					}
					else if (units.size() > 0) {
						for (int i = 0; i < units.size(); i++) {
							for (int j = i + 1; j <= units.size() - 1; j++) {
								if (units.at(i)->getCordX() == units.at(j)->getCordX() && units.at(i)->getCordY() == units.at(j)->getCordY()) {
									spondState = false;
								}
							}
							if (spondState) {
								units.push_back(new Hero(mouseController->getMouseX(), mouseController->getMouseY(), "Hero", 5500, 5));
								spondState = false;
							}
						}
					}
				}*/
			}
			else {
				printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), false);
			}
			
		}
		printController->printOnScreen();
		unitsController->mouveUnits();
		printController->updateScreenSize();
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete printController;
	delete mouseController;
	delete unitsController;

	for (auto& i : units) {
		delete i;
	}

	units.clear();
}

void saveGame() {
	try {
		std::ofstream file("saveGame.txt");
		std::string heroInfo;

		for (auto hero : units) {
			heroInfo += mumberToString(hero->getCordX()) + "," + mumberToString(hero->getCordY()) + "," + mumberToString(hero->getDestinationClickCordX()) + "," + mumberToString(hero->getDestinationClickCordY()) + "," + mumberToString(hero->getMoving()) + "," + mumberToString(hero->getSelected()) + "," + hero->getName() + "\n";
		}

		file << heroInfo;
		file.close();
	}
	catch (const std::exception& e) {
		e.what();
	}
}

void loadGame() {
	std::ifstream file("saveGame.txt");
	
	if (!file) {
		return;
	}

	try {
		std::string fileData;
		std::string args;
		std::vector<std::string> temp;
		int counter = 0;

		while (std::getline(file, fileData)) {
			for (int i = 0; i < fileData.length(); i++) {
				if (fileData[i] == ',') {
					temp.push_back(args);
					args = "";
				}
				else {
					args += fileData[i];
				}
			}
			
			temp.push_back(args);
			args = "";
			units.push_back(new Hero(stringToNumber<int>(temp.at(0)), stringToNumber<int>(temp.at(1)), temp.at(6), 5500, 5));

			units[counter]->setDestinationClickCordX(stringToNumber<int>(temp.at(2)));
			units[counter]->setDestinationClickCordY(stringToNumber<int>(temp.at(3)));
			units[counter]->setMoving(stringToNumber<int>(temp.at(4)));
			units[counter]->setSelected(stringToNumber<int>(temp.at(5)));

			temp = std::vector<std::string>();
			counter++;
		}
	}
	catch (const std::exception& e) {
		e.what();
	}
}