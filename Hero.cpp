#include "Hero.h"

Hero::Hero(int x, int y, std::string name, int xp, int lvl) : BaseUnit(x, y, name) {
	this->selected = false;
	this->moving = false;
	this->level = lvl;
	this->experience = xp;
}
