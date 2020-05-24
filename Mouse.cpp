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

void Mouse::calculatePosition() {
	if (!SetConsoleMode(mHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) {

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
						for (int m = 0; m < 5; m++)
							this->mouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;

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

	/*for (int m = 0; m < 5; m++)
	{
		m_mouse[m].bPressed = false;
		m_mouse[m].bReleased = false;

		if (mouseNewState[m] != m_mouseOldState[m])
		{
			if (m_mouseNewState[m])
			{
				m_mouse[m].bPressed = true;
				m_mouse[m].bHeld = true;
			}
			else
			{
				m_mouse[m].bReleased = true;
				m_mouse[m].bHeld = false;
			}
		}

		m_mouseOldState[m] = m_mouseNewState[m];
	}*/

}

int Mouse::getMouseX() {
	return this->mouseX;
}

int Mouse::getMouseY() {
	return this->mouseY;
}
