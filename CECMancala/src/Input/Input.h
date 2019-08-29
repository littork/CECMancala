#pragma once

#include <windows.h>

#include <Signal.h>

class Input {
private:
	Input() {};
private:
	static bool keyStates[36];
public:
	static bool isKeyPressed(const unsigned __int16& key);
public:
	static Signal<char> SignalKeyPress;
	static Signal<char> SignalKeyRelease;
public:
	static void refresh();
};