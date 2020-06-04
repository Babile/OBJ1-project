#include "Mouse.h"
#include <Windows.h>

HANDLE mHandle;
INPUT_RECORD inBuf[32];
DWORD events = 0;

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
				this->mouseConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
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
							this->mouseNewState[0] = true;
						}
						else if (inBuf[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
							this->mouseNewState[1] = true;
						}
						else {
							this->mouseNewState[0] = false;
							this->mouseNewState[1] = false;
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

	for (int i = 0; i < 2; i++) {
		if (this->mouseOldState[i] != this->mouseNewState[i]) {
			if (this->mouseNewState[i]) {
				this->mouseStates[i].pressed = true;
				this->mouseStates[i].hold = true;
				this->mouseStates[i].released = false;
			}
			else {
				this->mouseStates[i].released = true;
				this->mouseStates[i].pressed = false;
				this->mouseStates[i].hold = false;
			}
		}

		this->mouseOldState[i] = this->mouseNewState[i];
	}
}

int Mouse::getMouseX() {
	return this->mouseX;
}

int Mouse::getMouseY() {
	return this->mouseY;
}

bool Mouse::getMouseConsoleInFocus() {
	return this->mouseConsoleInFocus;
}

MouseKeyState Mouse::getMouseState(int whichButton) {
	return this->mouseStates[whichButton];
}
