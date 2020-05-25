#ifndef BASEUNIT_H
#define BASEUNIT_H

class BaseUnit {
protected:
	int cordX, cordY;
	bool selected;
public:
	BaseUnit(int cordX, int cordY);
	int gerCordX();
	int getCordY();
	void setCordX(int cordX);
	void setCordY(int cordY);
	bool getSelected();
	void setSelected(bool select);
};

#endif
