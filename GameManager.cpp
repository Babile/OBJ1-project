#include "GameManager.h"
#include "View.h"
#include "Mouse.h"

View *demo;
Mouse* mouse;

GameManager::GameManager() {
	demo = new View();
	mouse = new Mouse();
}

void GameManager::startAplication() {
	while (1) {
		mouse->calculatePosition();
		demo->printOnScreen(mouse->getMouseX(), mouse->getMouseY());
		demo->updateScreenSize();
	}
	clearBeforeClose();
}

void GameManager::clearBeforeClose() {
	delete demo;
}
