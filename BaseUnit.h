#ifndef BASEUNIT_H
#define BASEUNIT_H
#include <iostream>

class BaseUnit {
protected:
	int cordX, cordY;
	bool selected;
	bool moving;
	std::string name;
public:
	BaseUnit();
	BaseUnit(int cordX, int cordY, std::string name);
	int getCordX();
	int getCordY();
	void setCordX(int cordX);
	void setCordY(int cordY);
	bool getSelected();
	void setSelected(bool select);
	bool getMoving();
	void setMoving(bool move);
	std::string getName();
};

#endif
