#pragma once

#include <Signal.h>

class Engine {
private:
	Engine() {};
protected:
	static bool looping;
	static bool initialized;
public:
	static void init();
public:
	static void loop();
public:
	static Signal<> SignalRender;
public:
	static void inputEvent(const char& key);
};