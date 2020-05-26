#ifndef BASEUNIT_H
#define BASEUNIT_H
#include <iostream>

class BaseUnit {
protected:
	int cordX, cordY;
	bool selected;
	std::string name;
public:
	BaseUnit();
	BaseUnit(int cordX, int cordY, std::string name);
	int gerCordX();
	int getCordY();
	void setCordX(int cordX);
	void setCordY(int cordY);
	bool getSelected();
	void setSelected(bool select);
	std::string getName();
};

#endif
