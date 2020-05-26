#include "GameManager.h"
#include "View.h"
#include "Mouse.h"
#include "Hero.h"
#include "Controller.h"

View *printController;
Mouse* mouseController;
Controller* controller;
std::vector<BaseUnit*> units;

GameManager::GameManager() {
	printController = new View();
	mouseController = new Mouse();
	controller = new Controller();
}

void GameManager::startAplication() {
	while (1) {
		mouseController->calculateMousePositionAndClick();
		if (mouseController->getMouseLeftClick() && mouseController->getMouseState(0).bHeld) {
			printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), mouseController->getMouseState(0).bHeld, false);
			printController->printOnScreen();
		}
		else if (mouseController->getMouseRightClick() && mouseController->getMouseState(1).bHeld) {
			printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), false, mouseController->getMouseState(1).bHeld);
			printController->printOnScreen();
			units.push_back(new Hero(mouseController->getMouseX(), mouseController->getMouseY(), "Hero", 5500, 5));
		}
		else {
			printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), false, false);
			printController->printOnScreen();
		}
		printController->updateScreenSize();
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete printController;
	delete mouseController;

	for (auto& i : units) {
		delete i;
	}

	units.clear();
}
