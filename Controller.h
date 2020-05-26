#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
	Controller();
	void mouveUnits(int mouseCordX, int mouseCordY, bool mouseLeftClick, bool mouseLeftHold, bool mouseLeftReleased, bool mouseRightClick, bool mouseRightHold, bool mouseRightReleased);
};
#endif 