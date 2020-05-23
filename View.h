#ifndef VIEW_H
#define VIEW_H

class View {
private:
	int screenWidth, screenHeight;
public:
	View();
	void printOnScreen();
	bool updateScreenSize();
};

#endif

