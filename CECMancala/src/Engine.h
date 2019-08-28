#pragma once

#include <Signal.h>

class Engine {
public:
	Engine();
protected:
	bool looping;
public:
	void loop();
public:
	static Signal<> SignalRender;
};