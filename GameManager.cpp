#include "GameManager.h"
#include "View.h"

View *demo;

GameManager::GameManager() {
	demo = new View();
}

void GameManager::startAplication() {
	while (1) {
		demo->printOnScreen();
		demo->updateScreenSize();
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete demo;
}
