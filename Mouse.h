#ifndef MOUSE_H
#define MOUSE_H

struct MouseKeyState {
	bool bPressed;
	bool bReleased;
	bool bHeld;
};

class Mouse {
private:
	int mouseX;
	int mouseY;
	bool mouseLeftClick = false;
	bool mouseRightClick = false;
	bool mouseConsoleInFocus = true;
public:
	Mouse();
	void calculateMousePositionAndClick();
	int getMouseX();
	int getMouseY();
	bool getMouseLeftClick();
	bool getMouseRightClick();
	bool getMouseConsoleInFocus();
	MouseKeyState getMouseState(int whichButton);
};

#endif // !MOUSE_H
