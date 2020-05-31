#ifndef BASEUNIT_H
#define BASEUNIT_H
#include <iostream>

class BaseUnit {
protected:
	int cordX, cordY;
	int moveCordX, moveCordY;
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
	int getDestinationClickCordX();
	int getDestinationClickCordY();
	void setDestinationClickCordX(int cordX);
	void setDestinationClickCordY(int cordY);
	void setMoveCordX(int cordX);
	void setMoveCordY(int cordY);
	std::string getName();
};

#endif
