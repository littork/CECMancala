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

std::string parseResult(const unsigned __int8 gameResult) {
	switch (gameResult) {
	case 0:
		return "won";
		break;
	case 1:
		return "lost";
		break;
	case 2:
		return "tied";
		break;
	}
	return "";
}

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

unsigned __int8 encodePick(const char& character) {
	switch (character) {
	case 'R':
		return 0;
		break;
	case 'P':
		return 1;
		break;
	case 'S':
		return 2;
		break;
	default:
		return -1;
		break;
	}
}

int main() {
	Engine::init();

	std::string activeEntry = "";
	unsigned __int8 gameResult = 0;

	unsigned __int8 computerPick = 0;
	unsigned __int8 userPick = 0;

	unsigned __int64 gamesWon = 0;
	unsigned __int64 gamesLost = 0;
	unsigned __int64 gamesTied = 0;

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		switch (State::getState()) {
		case 0:
			Renderer::drawText(0, 0, "Do you pick (r)ock, (p)aper, or (s)cissors? " + activeEntry);
			break;
		case 1:
			Renderer::drawText(0, 0, "Your pick: " + parsePick(userPick));
			Renderer::drawText(0, 1, "Computer pick: " + parsePick(computerPick));
			Renderer::drawText(0, 2, "You " + parseResult(gameResult) + ".");
			Renderer::drawText(0, 3, "Press enter to play again, or escape to quit.");
			break;
		}

		Renderer::drawLine(48, 2, 48, 4, '|');
		Renderer::drawLine(49, 1, 80, 1, '_');
		Renderer::drawLine(49, 4, 80, 4, '_');
		Renderer::drawLine(80, 2, 80, 4, '|');

		Renderer::drawText(50, 2, "Games won/lost/tied: " + std::to_string(gamesWon) + "/" + std::to_string(gamesLost) + "/" + std::to_string(gamesTied));
		Renderer::drawText(50, 3, "Total games played: " + std::to_string(gamesWon + gamesLost + gamesTied));
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
			userPick = encodePick(activeEntry[0]);
			activeEntry = "";
			computerPick = std::rand() % 3;

			{
				gameResult = ((computerPick == userPick) ? 2 : ((userPick == 0) ? ((computerPick == 1) ? 1 : 0) : ((userPick == 1) ? ((computerPick == 2) ? 1 : 0) : ((computerPick == 0) ? 1 : 0))));
				switch (gameResult) {
				case 0:
					gamesWon++;
					break;
				case 1:
					gamesLost++;
					break;
				case 2:
					gamesTied++;
					break;
				}
			}

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
		case 1:
			if (key == Key::Esc) {
				Engine::looping = false;
				return;
			}

			if (key == Key::Return) {
				State::setState(0);
				return;
			}

			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}