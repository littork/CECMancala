#pragma once

#include <Engine/Signal.h>

class Engine {
private:
	Engine() {};
public:
	static bool looping;
protected:
	static bool initialized;
public:
	static void init();
	static void deinit();
public:
	static void loop();
	static void render();
public:
	static Signal<> SignalRender;

	static Slot_Scoped<char> SlotKeyPress;
public:
	static void inputEvent(const char& key);
};