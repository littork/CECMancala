#include "Input.h"

#include <iostream>

Signal<char> Input::SignalKeyPress = Signal<char>();
bool Input::keyStates[25] = { false };

bool Input::isKeyPressed(const unsigned __int16& key) {
	return GetKeyState(key) & 0x8000;
}

void Input::refresh() {
	for (unsigned __int8 i = 65; i <= 90; i++) {
		if (!keyStates[i - 65] && isKeyPressed(i)) {
			keyStates[i - 65] = true;
			SignalKeyPress.emit(i);
		} else if (keyStates[i - 65]) {
			keyStates[i - 65] = false;
		}
	}
}