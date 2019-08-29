#include "Engine.h"

#include <Renderer/Renderer.h>
#include <Console/Console.h>

#include <chrono>

#include <Input/Input.h>

#include <Macros.h>

Signal<> Engine::SignalRender = Signal<>();
Slot_Scoped<char> Engine::SlotKeyPress = Slot_Scoped<char>();

bool Engine::looping = false;
bool Engine::initialized = false;

void Engine::init() {
	if (initialized) {
		return;
	}
	initialized = true;

	looping = true;

	Console::init();
	Renderer::init();

	SlotKeyPress = Input::SignalKeyPress.connect(&inputEvent);
}

void Engine::deinit() {
	if (!initialized) {
		return;
	}
	initialized = false;

	
}

void Engine::inputEvent(const char& key) {
	// Console::log("Key pressed: ", key);
}

void Engine::loop() {
	init();

	auto lastTime = std::chrono::high_resolution_clock::now();
	auto startTime = std::chrono::high_resolution_clock::now();

	while (looping) {
		const unsigned __int64 timeDiffMs = (std::chrono::high_resolution_clock::now() - lastTime).count() / 1000000;

		{
			Input::refresh();
		}

		if (timeDiffMs < RENDER_FREQUENCY_MS) {
			continue;
		}

		Console::reset();

		//Console::log("Test - ", (std::chrono::high_resolution_clock::now() - startTime).count(), " - ", Input::isKeyPressed('X'));
		SignalRender.emit();

		//Renderer::drawLine(0, 0, 95, 27, '*');
		Renderer::drawLine(0, 0, 24, 0, '+');
		Renderer::drawLine(0, 0, 0, 24, '|');
		Renderer::drawLine(0, 0, 24, 24, '*');

		Renderer::flush();

		lastTime = std::chrono::high_resolution_clock::now();
	}
}