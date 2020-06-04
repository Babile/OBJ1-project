#include "View.h"
#include "GameManager.h"
#include <Windows.h>

HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten = 0;

int mouseXCord = 0, mouseYCord = 0;
int newMouseXCord = 0, newMouseYCord = 0;
bool mouseLeftHold = false;
bool mouseFirstLeftClick = false;
bool unitPrint = false;

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
			unitPrint = false;
			for (int k = 0; k < units.size(); k++) {
				if (j == units.at(k)->getCordX() && i == units.at(k)->getCordY()) {
					this->pScreenArray[i * screenWidth + j] = (unsigned char)(157);
					unitPrint = true;
					break;
				}
			}
			//to do select in other way
			if (((mouseYCord == i && (j >= mouseXCord && j <= newMouseXCord)) ||
				(mouseXCord == j && (i >= mouseYCord && i <= newMouseYCord)) ||
				(newMouseYCord == i && (j >= mouseXCord && j <= newMouseXCord)) ||
				(newMouseXCord == j && (i >= mouseYCord && i <= newMouseYCord))) && mouseLeftHold) {
				this->pScreenArray[i * screenWidth + j] = (unsigned char)(176);
			}
			else {
				if (!unitPrint) {
					this->pScreenArray[i * screenWidth + j] = ' ';
				}
			}
		}
	}
	wsprintf(&this->pScreenArray[this->screenWidth], "Units created: %d", BaseUnit::unitCount);
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

void View::gatherInformation(int mouseX, int mouseY, bool buttonLeftHold) {
	newMouseXCord = mouseX;
	newMouseYCord = mouseY;
	if (buttonLeftHold && !mouseFirstLeftClick) {
		mouseXCord = mouseX;
		mouseYCord = mouseY;
		mouseFirstLeftClick = true;
	}
	else if (!buttonLeftHold && mouseFirstLeftClick) {
		mouseFirstLeftClick = false;
	}
	mouseLeftHold = buttonLeftHold;
}
