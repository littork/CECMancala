/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Guessing game
*/

#include <Console/Console.h>
#include <Renderer/Renderer.h>
#include <Input/Input.h>
#include <Engine.h>
#include <memory>

int main() {
	Engine::init();

	int state = 0;

	std::string activeEntry = "";
	unsigned __int64 topScore = 0;
	unsigned __int64 lastGuess = 0;

	Engine::SignalRender.connect([&]() {
		if (state < 0) {
			Engine::looping = false;
			return;
		}

		switch (state) {
		case 0:
			Renderer::drawText(0, 0, "Enter the maximum number you wish to guess for: " + activeEntry);
			break;
		case 1:
			Renderer::drawText(0, 0, "Guess a number between 0 and " + std::to_string(topScore) + ": " + activeEntry);
			break;
		case 2:
			Renderer::drawText(0, 0, "You guessed " + std::to_string(lastGuess) + ". That number is either too high, too low, or correct. Press enter to guess again.");
			break;
		case 3:
			Renderer::drawText(0, 0, "That number is out of range, press enter to try again");
			break;
		}
	});

	Input::SignalKeyPress.connect([&](const char& key) {
		if (state < 0) {
			Engine::looping = false;
			return;
		}

		switch (state) {
		case 0:
			if (key == 13) {
				state = 1;
				topScore = std::stoi(activeEntry);
				activeEntry = "";
				Engine::render();
			}

			if (key >= '0' && key <= '9') {
				activeEntry += key;
				Engine::render();
				return;
			}
			break;
		case 1:
			if (key == 13) {
				state = 2;
				lastGuess = std::stoi(activeEntry);

				if (lastGuess > topScore) { // Would be handled in state machine normally
					state = 3;
				}

				activeEntry = "";
				Engine::render();
			}

			if (key >= '0' && key <= '9') {
				activeEntry += key;
				Engine::render();
				return;
			}
			break;
		case 3:
			if (key == 13) {
				state = 0;

				topScore = 0;
				activeEntry = "";
				lastGuess = 0;

				Engine::render();
			}
			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}