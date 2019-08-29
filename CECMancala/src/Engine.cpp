#include "Engine.h"

#include <Renderer/Renderer.h>
#include <Console/Console.h>

#include <chrono>

#include <Input/Input.h>

#include <Macros.h>

#include <cstdlib>

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

void Engine::render() {
	Console::reset();

	//Console::log("Test - ", (std::chrono::high_resolution_clock::now() - startTime).count(), " - ", Input::isKeyPressed('X'));
	SignalRender.emit();

	// char characterSet[10] = { '_', '-', '=', '+', 'O', '0', '%', '&', '^', '*' };

	/*for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
	Renderer::drawLine(x, 0, x, GRID_Y_WIDTH - 1, rand() % 15 + 60);
	}*/

	/*for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
	for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
	Renderer::draw(x, y, rand() % 15 + 60);
	}
	}*/

	//Renderer::drawLine(0, 0, 24, 0, '+');
	//Renderer::drawLine(0, 0, 0, 24, '|');
	//Renderer::drawLine(0, 0, 24, 24, '*');

	/*for (unsigned int x = 0; x < (frameCounter*10 < GRID_X_WIDTH ? frameCounter*10 : GRID_X_WIDTH); x++) {
	float y = ((float) x / (float) GRID_X_WIDTH) * ((float) GRID_Y_WIDTH);

	Renderer::drawLine(x, 0, 0, y, '*');
	}*/

	/*for (unsigned int x = GRID_X_WIDTH - 1; x > 0; x--) {
	float y = (((float) GRID_X_WIDTH - (float) x) / (float) GRID_X_WIDTH) * ((float) GRID_Y_WIDTH);

	Renderer::drawLine(GRID_X_WIDTH - 1, y, x, 0, '*');
	}*/

	Renderer::flush();
}

void Engine::loop() {
	init();

	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>();
	std::chrono::steady_clock::time_point lastInputTime = std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>();
	auto startTime = CHRONO_NOW();

	unsigned int frameCounter = 0;

	while (looping) {
		const unsigned __int64 frameDiffMs = (CHRONO_NOW() - lastFrameTime).count() / 1000000;
		const unsigned __int64 inputDiffMs = (CHRONO_NOW() - lastInputTime).count() / 1000000;

		if (inputDiffMs > INPUT_FREQUENCY_MS) {
			Input::refresh();
			lastInputTime = CHRONO_NOW();
		}

		if (frameDiffMs < RENDER_FREQUENCY_MS) {
			continue;
		}

		render();

		frameCounter++;
		lastFrameTime = CHRONO_NOW();
	}
}