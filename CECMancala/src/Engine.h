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
	static void deinit();
public:
	static void loop();
public:
	static Signal<> SignalRender;

	static Slot_Scoped<char> SlotKeyPress;
public:
	static void inputEvent(const char& key);
};