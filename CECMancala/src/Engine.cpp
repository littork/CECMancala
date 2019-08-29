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

	auto lastFrameTime = CHRONO_NOW();
	auto lastInputTime = lastFrameTime;
	auto startTime = lastFrameTime;

	unsigned int frameCounter = 0;

	while (looping) {
		const unsigned __int64 frameDiffMs = (CHRONO_NOW() - lastFrameTime).count() / 1000000;
		const unsigned __int64 inputDiffMs = (CHRONO_NOW() - lastInputTime).count() / 1000000;

		if (inputDiffMs < INPUT_FREQUENCY_MS) {
			Input::refresh();
			lastInputTime = CHRONO_NOW();
		}

		if (frameDiffMs < RENDER_FREQUENCY_MS) {
			continue;
		}

		Console::reset();

		//Console::log("Test - ", (std::chrono::high_resolution_clock::now() - startTime).count(), " - ", Input::isKeyPressed('X'));
		SignalRender.emit();

		/*Renderer::drawLine(0, 0, 24, 0, '+');
		Renderer::drawLine(0, 0, 0, 24, '|');
		Renderer::drawLine(0, 0, 24, 24, '*');*/
		
		for (unsigned int x = 0; x < (frameCounter*10 < GRID_X_WIDTH ? frameCounter*10 : GRID_X_WIDTH); x++) {
			float y = ((float) x / (float) GRID_X_WIDTH) * ((float) GRID_Y_WIDTH);

			Renderer::drawLine(x, 0, 0, y, '*');
		}

		for (unsigned int x = GRID_X_WIDTH - 1; x > 0; x--) {
			float y = (((float) GRID_X_WIDTH - (float) x) / (float) GRID_X_WIDTH) * ((float) GRID_Y_WIDTH);

			Renderer::drawLine(GRID_X_WIDTH - 1, y, x, 0, '*');
		}

		Renderer::flush();

		frameCounter++;
		lastFrameTime = CHRONO_NOW();
	}
}