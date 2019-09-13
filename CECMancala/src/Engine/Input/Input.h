#pragma once

#include <windows.h>

#include <Engine/Signal.h>

class Input {
private:
	Input() {};
private:
	static bool keyStates[39];
	static char specialKeys[3];
public:
	static bool isKeyPressed(const unsigned __int16& key);
public:
	static Signal<char> SignalKeyPress;
	static Signal<char> SignalKeyRelease;
public:
	static void refresh();
};