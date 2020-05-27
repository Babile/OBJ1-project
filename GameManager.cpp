#include "GameManager.h"
#include "View.h"
#include "Mouse.h"
#include "Hero.h"
#include "Controller.h"
#include <Windows.h>

View *printController;
Mouse* mouseController;
Controller* controller;
std::vector<BaseUnit*> units;
bool spondState = true;
bool safeRightButtonPress = false;
int oldMouseCordX = 0, oldMouseCordY = 0;

GameManager::GameManager() {
	printController = new View();
	mouseController = new Mouse();
	controller = new Controller();
	this->gameRunning = true;
}

void GameManager::startAplication() {
	while (this->gameRunning) {
		if (GetAsyncKeyState((unsigned short)27) & 0x8000) {
			this->gameRunning = false;
		}
		else {
			spondState = true;
			mouseController->calculateMousePositionAndClick();
			if (mouseController->getMouseLeftClick() && !mouseController->getMouseState(0).bReleased) {
				if (mouseController->getMouseState(0).bPressed) {
					for (int i = 0; i < units.size(); i++) {
						if (mouseController->getMouseX() == units.at(i)->getCordX() && mouseController->getMouseY() == units.at(i)->getCordY()) {
							units.at(i)->setSelected(true);
						}
						else {
							units.at(i)->setSelected(false);
						}
					}
				}
				if (mouseController->getMouseState(0).bHeld) {
					printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), mouseController->getMouseState(0).bHeld, false);
				}
			}

			else if (mouseController->getMouseRightClick() && !mouseController->getMouseState(1).bReleased) {
				for (int i = 0; i < units.size(); i++) {
					if (units.at(i)->getSelected()) {
						units.at(i)->setMoving(true);
						spondState = false;
					}
				}
				if (mouseController->getMouseState(1).bPressed) {
					safeRightButtonPress = true;
					oldMouseCordX = mouseController->getMouseX();
					oldMouseCordY = mouseController->getMouseY();
				}
				if (spondState) {
					if (units.size() == 0) {
						units.push_back(new Hero(mouseController->getMouseX(), mouseController->getMouseY(), "Hero", 5500, 5));
						spondState = false;
					}
					else if (units.size() > 0) {
						for (int i = 0; i < units.size(); i++) {
							for (int j = i + 1; j <= units.size() - 1; j++) {
								if (units.at(i)->getCordX() != units.at(j)->getCordX() && units.at(i)->getCordY() != units.at(j)->getCordY()) {
									units.push_back(new Hero(mouseController->getMouseX(), mouseController->getMouseY(), "Hero", 5500, 5));
									spondState = false;
								}
							}
						}
					}
				}
			}
			else {
				printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), false, false);
			}

			if (safeRightButtonPress) {
				controller->mouveUnits(oldMouseCordX, oldMouseCordY);
			}	
			printController->printOnScreen();
			printController->updateScreenSize();
		}
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete printController;
	delete mouseController;
	delete controller;

	for (auto& i : units) {
		delete i;
	}

	units.clear();
}
