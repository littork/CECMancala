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

	unsigned int totalGuesses = 0;
	unsigned int totalGames = 0;
	unsigned int currentGuesses = 0;
	unsigned int mostGuesses = 0;
	unsigned int leastGuesses = 0;

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

		Renderer::drawText(0, 1, "Total Guesses: " + std::to_string(totalGuesses));
		Renderer::drawText(0, 2, "Total Games Played: " + std::to_string(totalGames));
		Renderer::drawText(0, 3, "Most/Least Guesses: " + std::to_string(mostGuesses) + "/" + std::to_string(leastGuesses));
		if (totalGuesses > 0 && totalGames > 0) {
			Renderer::drawText(0, 4, "Average number of guesses taken to win each game: " + std::to_string((float)totalGuesses / (float)totalGames));
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
			currentGuesses = 0;
			break;
		}

		switch (newState) {
		case 0:
			maxScore = 0;
			activeEntry = "";
			lastGuess = 0;
			break;
		case 1:
			if (lastGuess == actualNumber) {
				State::setState(0);
			}
			activeEntry = "";
			break;
		case 2:
			totalGuesses++;
			currentGuesses++;
			if (currentGuesses > mostGuesses) {
				mostGuesses = currentGuesses;
			}
			if (leastGuesses > currentGuesses) {
				leastGuesses = currentGuesses;
			}
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
				guessResult = "correct! Press enter to restart";
				break;
			}
			guessResult += " Press enter to guess again";

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
			if (lastGuess == actualNumber) {
				totalGames++;
			}

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