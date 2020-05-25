#include "Mouse.h"
#include <Windows.h>

HANDLE mHandle;
INPUT_RECORD inBuf[32];
DWORD events = 0;
MouseKeyState mouseStates[2];
bool oldMouseLeftClick = false;
bool oldMouseRightClick = false;

Mouse::Mouse() {
	this->mouseX = 0;
	this->mouseY = 0;
	mHandle = GetStdHandle(STD_INPUT_HANDLE);
	GetNumberOfConsoleInputEvents(mHandle, &events);
	
}

void Mouse::calculateMousePositionAndClick() {
	if (!SetConsoleMode(mHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) {
		//todo error hendler
	}

	if (events > 0) {
		ReadConsoleInput(mHandle, inBuf, events, &events);
	}
	
	for (DWORD i = 0; i < events; i++) {
		switch (inBuf[i].EventType) {
			case FOCUS_EVENT: {
				mouseConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
			}
			break;
			case MOUSE_EVENT: {
				switch (inBuf[i].Event.MouseEvent.dwEventFlags) {
					case MOUSE_MOVED: {
						this->mouseX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
						this->mouseY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
					}
					break;
					case 0: {
						if (inBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
							this->mouseLeftClick = true;
							if (!oldMouseLeftClick && this->mouseLeftClick) {
								mouseStates[0].bPressed = true;
								mouseStates[0].bReleased = false;
								oldMouseLeftClick = true;
							}
							else if (oldMouseLeftClick && this->mouseLeftClick) {
								mouseStates[0].bPressed = true;
								mouseStates[0].bHeld = true;
								mouseStates[0].bReleased = false;
							}
							else if (oldMouseLeftClick && !this->mouseLeftClick) {
								mouseStates[0].bPressed = false;
								mouseStates[0].bHeld = false;
								mouseStates[0].bReleased = true;
								oldMouseLeftClick = false;
							}
						}
						else if (inBuf[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
							this->mouseRightClick = true;
							if (!oldMouseRightClick && this->mouseRightClick) {
								mouseStates[1].bPressed = true;
								mouseStates[1].bReleased = false;
								oldMouseRightClick = true;
							}
							else if (oldMouseRightClick && this->mouseRightClick) {
								mouseStates[1].bPressed = true;
								mouseStates[1].bHeld = true;
								mouseStates[1].bReleased = false;
							}
							else if (oldMouseRightClick && !this->mouseRightClick) {
								mouseStates[1].bPressed = false;
								mouseStates[1].bHeld = false;
								mouseStates[1].bReleased = true;
								oldMouseRightClick = false;
							}
						}
						else {
							this->mouseLeftClick = false;
							this->mouseRightClick = false;
							for (int i = 0; i < 2; i++) {
								mouseStates[i].bPressed = false;
								mouseStates[i].bHeld = false;
								mouseStates[i].bReleased = false;
							}
						}
					}
					break;

					default:
						break;
					}
			}
			break;
			default:
				break;
		}
	}
}

int Mouse::getMouseX() {
	return this->mouseX;
}

int Mouse::getMouseY() {
	return this->mouseY;
}

bool Mouse::getMouseLeftClick() {
	return this->mouseLeftClick;
}

bool Mouse::getMouseRightClick() {
	return this->mouseRightClick;
}

bool Mouse::getMouseConsoleInFocus() {
	return this->mouseConsoleInFocus;
}

MouseKeyState Mouse::getMouseState(int whichButton) {
	return mouseStates[whichButton];
}
