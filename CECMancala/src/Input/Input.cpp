#include "Input.h"

Signal<char> Input::SignalKeyPress = Signal<char>();

bool Input::isKeyPressed(const unsigned __int16& key) {
	return GetKeyState(key) & 0x8000;
}

void Input::refresh() {
	for (unsigned __int8 i = 65; i <= 90; i++) {
		if (isKeyPressed(i)) {
			SignalKeyPress.emit(i);
		}
	}
}