#include "Controller.h"
#include "GameManager.h"
#include <chrono>

float fElapsedTime = 0.0f;
float gameSpeedX = 0.5f, gameSpeedY = 0.5f;

auto tp1 = std::chrono::system_clock::now();
auto tp2 = std::chrono::system_clock::now();

Controller::Controller() {}

void Controller::mouveUnits() {
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = tp2 - tp1;
	tp1 = tp2;
	fElapsedTime = elapsedTime.count();

	for (int i = 0; i < units.size(); i++) {
		//red
		if (units.at(i)->getDestinationClickCordX() > units.at(i)->getCordX()) {
			gameSpeedX = 0.5f;
		}
		else if (units.at(i)->getDestinationClickCordX() < units.at(i)->getCordX()) {
			gameSpeedX = -0.5f;
		}
		//kolona
		if (units.at(i)->getDestinationClickCordY() > units.at(i)->getCordY()) {
			gameSpeedY = 0.5f;
		}
		else if (units.at(i)->getDestinationClickCordY() < units.at(i)->getCordY()) {
			gameSpeedY = -0.5f;
		}

		if (units.at(i)->getDestinationClickCordX() == units.at(i)->getCordX() && units.at(i)->getDestinationClickCordY() == units.at(i)->getCordY()) {
			units.at(i)->setMoving(false);
		}

		if (units.at(i)->getMoving()) {
			if (units.at(i)->getDestinationClickCordX() != units.at(i)->getCordX()) {
				units.at(i)->setCordX(units.at(i)->getCordX() + (gameSpeedX * fElapsedTime));
			}
			if (units.at(i)->getDestinationClickCordY() != units.at(i)->getCordY()) {
				units.at(i)->setCordY(units.at(i)->getCordY() + (gameSpeedY * fElapsedTime));
			}
		}
	}
}
