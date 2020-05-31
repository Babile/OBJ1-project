#ifndef MOUSE_H
#define MOUSE_H

struct MouseKeyState {
	bool pressed = false;
	bool released = false;
	bool hold = false;
};

class Mouse {
private:
	int mouseX;
	int mouseY;
	bool mouseOldState[2] = { 0 };
	bool mouseNewState[2] = { 0 };
	bool mouseConsoleInFocus = true;
	MouseKeyState mouseStates[2];
public:
	Mouse();
	void calculateMousePositionAndClick();
	int getMouseX();
	int getMouseY();
	bool getMouseConsoleInFocus();
	MouseKeyState getMouseState(int whichButton);
};

#endif
