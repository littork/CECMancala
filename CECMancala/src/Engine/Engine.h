#pragma once

#include <Engine/Signal.h>

#include <chrono>

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
	static Signal<> SignalTick;

	static Slot_Scoped<char> SlotKeyPress;
public:
	static std::chrono::steady_clock::time_point lastFrameTime;
	static std::chrono::steady_clock::time_point lastInputTime;
	static std::chrono::steady_clock::time_point lastTickTime;
public:
	static void inputEvent(const char& key);
};