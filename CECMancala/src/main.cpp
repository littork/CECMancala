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
#include <State.h>
#include <Engine.h>
#include <cstdlib>
#include <memory>

int main() {
	Engine::init();

	std::string activeEntry = "";

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

	// Input handler
	Slot_Scoped<char> SlotKeyPress = Input::SignalKeyPress.connect([&](const char& key) {
		switch (State::getState()) {
		case 0:
			if (key == Key::Return) {
				if (activeEntry.length()) {
					State::setState(1);
				}
				return;
			}

			if (key == Key::Backspace) {
				if (activeEntry.length()) {
					activeEntry = activeEntry.substr(0, activeEntry.length() - 1);
				}
				Engine::render();
				return;
			}

			if (key >= 'A' && key <= 'Z') {
				activeEntry += key;
				Engine::render();
				return;
			}
			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}