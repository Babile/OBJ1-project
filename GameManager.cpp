#include "GameManager.h"
#include "View.h"
#include "Mouse.h"
#include <vector>

View *printController;
Mouse* mouseController;
//std::vector<> units = new std::vector<>();

GameManager::GameManager() {
	printController = new View();
	mouseController = new Mouse();
}

void GameManager::startAplication() {
	while (1) {
		mouseController->calculateMousePositionAndClick();
		if (mouseController->getMouseLeftClick() && mouseController->getMouseState(0).bHeld) {
			printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), mouseController->getMouseState(0).bHeld, false);
			printController->printOnScreen();
		}
		else {
			printController->gatherInformation(mouseController->getMouseX(), mouseController->getMouseY(), mouseController->getMouseState(0).bHeld, false);
			printController->printOnScreen();
		}
		printController->updateScreenSize();
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete printController;
	delete mouseController;
}
