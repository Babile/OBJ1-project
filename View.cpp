#include "View.h"
#include <Windows.h>

char *pScreenArray;
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten = 0;

View::View() {
	SetConsoleActiveScreenBuffer(hConsole);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
	this->screenHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
	this->screenWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	pScreenArray = new char[this->screenHeight * this->screenWidth];
}

void View::printOnScreen() {
	for (int i = 0; i < this->screenHeight; i++) {
		for (int j = 0; j < this->screenWidth; j++) {
			pScreenArray[i * screenWidth + j] = '@';
		}
	}
	WriteConsoleOutputCharacter(hConsole, pScreenArray, this->screenWidth * this->screenHeight, { 0,0 }, &dwBytesWritten);
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
		delete[] pScreenArray;
		pScreenArray = new char[screenWidth * screenHeight];
		return true;
	}
	return false;
}
