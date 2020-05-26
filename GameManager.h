#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <iostream>
#include "BaseUnit.h"

extern std::vector<BaseUnit*> units;

class GameManager {
public: 
	GameManager();
	void startAplication();
	void clearBeforeClose();
};

#endif

