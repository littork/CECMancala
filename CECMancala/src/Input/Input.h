#pragma once

#include <windows.h>

#include <Signal.h>

class Input {
private:
	Input() {};
private:
	static bool keyStates[38];
	static char specialKeys[2];
public:
	static bool isKeyPressed(const unsigned __int16& key);
public:
	static Signal<char> SignalKeyPress;
	static Signal<char> SignalKeyRelease;
public:
	static void refresh();
};