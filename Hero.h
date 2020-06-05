#ifndef HERO_H
#define HERO_H
#include "BaseUnit.h"

class Hero : public BaseUnit {
private:
	int experience, level;
public:
	Hero(int x, int y, std::string string, int ex, int lvl);
	Hero& operator +=(const Hero& rhs);
};

#endif

