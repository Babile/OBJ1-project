#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
private:
	int mouseX;
	int mouseY;
	bool mouseNewState[5] = { 0 };
	bool mouseConsoleInFocus = true;
public:
	Mouse();
	void calculatePosition();
	int getMouseX();
	int getMouseY();
};

#endif // !MOUSE_H
