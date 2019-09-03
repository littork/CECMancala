#pragma once

#include <Signal.h>

class State {
private:
	State() {};
private:
	static int state;
public:
	static void setState(const int& _state);
	static int getState();
	static Signal<int, int> SignalStateChange;
};