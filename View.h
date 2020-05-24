#ifndef VIEW_H
#define VIEW_H

class View {
private:
	char* pScreenArray;
	int screenWidth, screenHeight;
public:
	View();
	void printOnScreen(int mouseX, int mouseY);
	bool updateScreenSize();
};

#endif

