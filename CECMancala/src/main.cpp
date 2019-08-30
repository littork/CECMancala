/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Guessing game based on:
		State machine
		Rendering system
		Input system
		Sigslot mechanism

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
	unsigned __int64 maxScore = 0;
	unsigned __int64 lastGuess = 0;

	unsigned __int64 actualNumber = 0;

	std::string guessResult = "";

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		switch (State::getState()) {
		case 0:
			Renderer::drawText(0, 0, "Enter the maximum number you wish to guess for: " + activeEntry);
			break;
		case 1:
			Renderer::drawText(0, 0, "Guess a number between 0 and " + std::to_string(maxScore) + ": " + activeEntry);
			break;
		case 2:
			Renderer::drawText(0, 0, "You guessed " + std::to_string(lastGuess) + ". That number is " + guessResult);
			break;
		case 3:
			Renderer::drawText(0, 0, "That number is out of range, press enter to try again");
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
			maxScore = std::stoi(activeEntry);
			actualNumber = rand() % (maxScore + 1);
			break;
		}

		switch (newState) {
		case 0:
			maxScore = 0;
			activeEntry = "";
			lastGuess = 0;
			break;
		case 1:
			activeEntry = "";
			break;
		case 2:
			lastGuess = std::stoi(activeEntry);
			activeEntry = "";
			if (lastGuess > maxScore) {
				State::setState(3);
			}

			guessResult = "";
			if (lastGuess > actualNumber) {
				guessResult = "too high.";
			} else if (lastGuess < actualNumber) {
				guessResult = "too low.";
			} else {
				guessResult = "correct! Press enter to restart.";
				break;
			}
			guessResult += " Press enter to guess again.";

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

			if (key >= '0' && key <= '9') {
				activeEntry += key;
				Engine::render();
				return;
			}
			break;
		case 1:
			if (key == Key::Return) {
				if (activeEntry.length()) {
					State::setState(2);
				}
			}

			if (key == Key::Backspace) {
				if (activeEntry.length()) {
					activeEntry = activeEntry.substr(0, activeEntry.length() - 1);
				}
				Engine::render();
				return;
			}

			if (key >= '0' && key <= '9') {
				activeEntry += key;
				Engine::render();
				return;
			}
			break;
		case 2:
			if (key == Key::Return) {
				State::setState(1);
			}
			break;
		case 3:
			if (key == Key::Return) {
				State::setState(0);
			}
			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}