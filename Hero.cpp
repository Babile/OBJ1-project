#include "Hero.h"

Hero::Hero(int x, int y, std::string string, int xp, int lvl) : BaseUnit(x, y, string) {
	this->selected = false;
	this->moving = false;
	this->level = lvl;
	this->experience = xp;
}
