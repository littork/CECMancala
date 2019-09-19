/*
Input.h

Dylan Pozarnsky

Monitors and tracks user input
*/

#pragma once

#include <windows.h>

#include <Engine/Signal.h>

class Input {
private:
	Input() {};
private:
	static bool keyStates[43];
	static char specialKeys[7];
public:
	static bool isKeyPressed(const unsigned __int16& key);
public:
	static Signal<char> SignalKeyPress;
	static Signal<char> SignalKeyRelease;
public:
	static void refresh();
};