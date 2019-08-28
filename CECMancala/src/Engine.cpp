#include "Engine.h"

#include <Renderer/Renderer.h>
#include <Console/Console.h>

#include <chrono>

#include <Input/Input.h>

#include <Macros.h>

Signal<> Engine::SignalRender = Signal<>();

Engine::Engine() : looping(true) {
	Renderer::init();

	Input::SignalKeyPress.connect()
}

void Engine::loop() {
	auto lastTime = std::chrono::high_resolution_clock::now();
	auto startTime = std::chrono::high_resolution_clock::now();

	while (looping) {
		const unsigned __int64 timeDiffMs = (std::chrono::high_resolution_clock::now() - lastTime).count() / 1000000;
		if (timeDiffMs < RENDER_FREQUENCY_MS) {
			continue;
		}

		Console::clear();

		Console::write("Test - ", (std::chrono::high_resolution_clock::now() - startTime).count(), " - ", Input::isKeyPressed('X'));
		SignalRender.emit();

		Renderer::flush();
		lastTime = std::chrono::high_resolution_clock::now();
	}
}