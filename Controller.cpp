#include "Controller.h"
#include "GameManager.h"
#include <chrono>

float fElapsedTime = 0.0f;
float gameSpeedX = 5.0f, gameSpeedY = 5.0f;

auto tp1 = std::chrono::system_clock::now();
auto tp2 = std::chrono::system_clock::now();

Controller::Controller() {}

void Controller::mouveUnits(int mouseCordX, int mouseCordY) {
	tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = tp2 - tp1;
	tp1 = tp2;
	fElapsedTime = elapsedTime.count();

	for (int i = 0; i < units.size(); i++) {
		//red
		if (mouseCordX > units.at(i)->getCordX()) {
			gameSpeedX = 0.5f;
		}
		else if (mouseCordX < units.at(i)->getCordX()) {
			gameSpeedX = -0.5f;
		}
		//kolona
		if (mouseCordY > units.at(i)->getCordY()) {
			gameSpeedY = 0.5f;
		}
		else if (mouseCordY < units.at(i)->getCordY()) {
			gameSpeedY = -0.5f;
		}

		if (mouseCordX == units.at(i)->getCordX() && mouseCordY == units.at(i)->getCordY()) {
			units.at(i)->setMoving(false);
		}
		else if (units.at(i)->getMoving()) {
			if (mouseCordX == units.at(i)->getCordX()) {
				units.at(i)->setCordX(units.at(i)->getCordX());
			}
			else {
				units.at(i)->setCordX(units.at(i)->getCordX() + (gameSpeedX * fElapsedTime));
			}
			if (mouseCordY == units.at(i)->getCordY()) {
				units.at(i)->setCordY(units.at(i)->getCordY());
			}
			else {
				units.at(i)->setCordY(units.at(i)->getCordY() + (gameSpeedY * fElapsedTime));
			}
		}
	}	
}
