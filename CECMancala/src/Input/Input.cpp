#include "Input.h"

Signal<char> Input::SignalKeyPress = Signal<char>();
Signal<char> Input::SignalKeyRelease = Signal<char>();
bool Input::keyStates[37] = { false };

bool Input::isKeyPressed(const unsigned __int16& key) {
	return GetKeyState(key) & 0x8000;
}

void Input::refresh() {
	for (unsigned __int8 i = 48; i <= 90; i == 57 ? i = 65 : i++) {
		const unsigned __int8 offset = i - (i > 57 ? 65 : 22);
		if (!keyStates[offset] && isKeyPressed(i)) {
			keyStates[offset] = true;
			SignalKeyPress.emit(i);
		} else if (keyStates[offset] && !isKeyPressed(i)) {
			keyStates[offset] = false;
			SignalKeyRelease.emit(i);
		}
	}

	if (!keyStates[36] && isKeyPressed(13)) { // Enter key
		keyStates[36] = true;
		SignalKeyPress.emit(13);
	} else if (keyStates[36] && !isKeyPressed(13)) {
		keyStates[36] = false;
		SignalKeyRelease.emit(13);
	}
}