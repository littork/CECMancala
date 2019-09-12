/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Rock Paper Scissors Project

	The engine is very incomplete.
*/

#include <Console/Console.h>
#include <Renderer/Renderer.h>
#include <Input/Input.h>
#include <Input/Keys.h>
#include <Input/UserInput.h>
#include <State.h>
#include <Engine.h>
#include <cstdlib>
#include <memory>

int main() {
	Engine::init();

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		switch (State::getState()) {
		case 0:
			
			break;
		}
	});

	// State machine
	Slot_Scoped<int, int> SlotStateChange = State::SignalStateChange.connect([&](const int& oldState, const int& newState) {
		if (newState < 0) {
			Engine::looping = false;
			return;
		}

		switch (oldState) {
		case 0:
			break;
		}

		switch (newState) {
		case 0:
			break;
		}

		Engine::render();
	});

	Slot_Scoped<std::string> SlotTextEntered = UserInput::SignalEntryEntered.connect([&](const std::string& text) {
		
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}