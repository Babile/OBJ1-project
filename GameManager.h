#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <iostream>
#include "BaseUnit.h"

extern std::vector<BaseUnit*> units;

class GameManager {
private:
	bool gameRunning;
	void gameThread();
	void clearBeforeClose();
public: 
	GameManager();
	void startAplication();
	
};

#endif

