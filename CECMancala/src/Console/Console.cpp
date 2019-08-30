#include "Console.h"

bool Console::initialized = false;
HANDLE Console::handle = HANDLE();
COORD Console::coordZero = COORD();
COORD Console::activeCoord = COORD();

void Console::reset() {
	init();

	SetConsoleCursorPosition(handle, coordZero);
}

void Console::init() {
	if (initialized) {
		return;
	}
	initialized = true;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	coordZero.X = 0;
	coordZero.Y = 0;

	// Adjust console to be more compatible with gaming
	setCursorVisible(false);
}

void Console::setCursorVisible(const bool& visible) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void Console::setCursorPosition(const unsigned int& x, const unsigned int& y) {
	init();

	activeCoord.X = x;
	activeCoord.Y = y;

	SetConsoleCursorPosition(handle, activeCoord);
}