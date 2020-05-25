#ifndef VIEW_H
#define VIEW_H

class View {
private:
	char* pScreenArray;
	int screenWidth, screenHeight;
public:
	View();
	void printOnScreen();
	bool updateScreenSize();
	void gatherInformation(int mouseX, int mouseY, bool buttonLeftHold, bool buttonRightHold);
};

#endif

