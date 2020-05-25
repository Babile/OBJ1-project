#include "View.h"
#include <Windows.h>

HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten = 0;
int mouseXCord = 0, mouseYCord = 0;
int newMouseXCord = 0, newMouseYCord = 0;
bool mouseLeftHold = false;
bool mouseRightHold = false;

View::View() {
	SetConsoleActiveScreenBuffer(hConsole);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
	SetConsoleTitle("OBJ1 project");
	this->screenHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
	this->screenWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	this->pScreenArray = new char[this->screenHeight * this->screenWidth];
}

void View::printOnScreen() {
	for (int i = 0; i < this->screenHeight; i++) {
		for (int j = 0; j < this->screenWidth; j++) {
			if (mouseXCord == j && mouseYCord == i && mouseLeftHold) {
				pScreenArray[i * screenWidth + j] = '@';
			}
			else {
				pScreenArray[i * screenWidth + j] = ' ';
			}
		}
	}

	WriteConsoleOutputCharacter(hConsole, this->pScreenArray, this->screenWidth * this->screenHeight, { 0,0 }, &dwBytesWritten);
}

bool View::updateScreenSize() {
	short int columns, rows;

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
	columns = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	rows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

	if (screenWidth != columns || screenHeight != rows) {
		this->screenWidth = columns;
		this->screenHeight = rows;
		bufferInfo.dwSize.X = columns;
		bufferInfo.dwSize.Y = rows;
		SetConsoleScreenBufferSize(hConsole, bufferInfo.dwSize);
		delete[] this->pScreenArray;
		this->pScreenArray = new char[screenWidth * screenHeight];
		return true;
	}
	return false;
}

void View::gatherInformation(int mouseX, int mouseY, bool buttonLeftHold, bool buttonRightHold) {
	mouseXCord = mouseX;
	mouseYCord = mouseY;
	mouseLeftHold = buttonLeftHold;
	mouseRightHold = buttonRightHold;
}
