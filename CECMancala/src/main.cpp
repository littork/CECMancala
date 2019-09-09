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

std::string parsePick(const unsigned __int8 pick) {
	switch (pick) {
	case 0:
		return "Rock";
		break;
	case 1:
		return "Paper";
		break;
	case 2:
		return "Scissors";
		break;
	}
	return "";
}

int main() {
	Engine::init();

	std::string activeEntry = "";

	unsigned __int8 computerPick = 0;

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		switch (State::getState()) {
		case 0:
			Renderer::drawText(0, 0, "Do you pick (r)ock, (p)aper, or (s)cissors? " + activeEntry);
			break;
		case 1:
			Renderer::drawText(0, 0, "Your pick: " + parsePick(computerPick));
			Renderer::drawText(0, 1, "Computer pick: " + parsePick(computerPick));
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
			if (activeEntry[0] != 'R' && activeEntry[0] != 'P' && activeEntry[0] != 'S') {
				activeEntry = "";
				State::setState(0);
				return;
			}
			break;
		}

		switch (newState) {
		case 0:
			break;
		case 1:
			computerPick = std::rand() % 3;
			break;
		case 2:
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