#include "Input.h"

#include "Keys.h"

Signal<char> Input::SignalKeyPress = Signal<char>();
Signal<char> Input::SignalKeyRelease = Signal<char>();
bool Input::keyStates[38] = { false };
char Input::specialKeys[2] = {Key::Return, Key::Backspace};

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

	// Special keys
	for (unsigned __int8 i = 36; i < 38; i++) {
		if (!keyStates[i] && isKeyPressed(specialKeys[i - 36])) {
			keyStates[i] = true;
			SignalKeyPress.emit(specialKeys[i - 36]);
		} else if (keyStates[i] && !isKeyPressed(specialKeys[i - 36])) {
			keyStates[i] = false;
			SignalKeyRelease.emit(specialKeys[i - 36]);
		}
	}
}