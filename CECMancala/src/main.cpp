/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Rock Paper Scissors Project

	The engine is very incomplete.
*/

#include <Engine/Engine_Core.h>

#include <cstdlib>
#include <memory>
#include <chrono>

#include <Mancala/Board.h>

int main() {
	Engine::init();

	std::shared_ptr<Board> board = std::make_shared<Board>();
	board->setup();

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		Renderer::drawSmartBox(0 - Renderer::window[0], 0 - Renderer::window[1], GRID_X_WIDTH - 1 - Renderer::window[0], GRID_Y_WIDTH - 1 - Renderer::window[1]);

		if (State::getState() > 0) {
			Renderer::drawTextAligned(79, 17, "Input Guide");
			Renderer::drawTextAligned(79, 18, "Arrow Keys: Change Selection");
			Renderer::drawTextAligned(79, 19, "Enter: Pick stones");
		}

		switch (State::getState()) {
		case 0:
			Renderer::drawFilledBox(1, 1, GRID_X_WIDTH - 2, GRID_Y_WIDTH - 1, L'\u2576');
			Renderer::drawTextAligned(48, 4, "CEC Mancala");
			Renderer::drawTextAligned(48, 6, "By Dylan Pozarnsky");
			Renderer::drawTextAligned(48, 12, "Press any key to begin");
			break;
		case 3:
		case 2:
		case 1:
			Renderer::drawLine(0, 16, 92, 16, L'\u2550');
			Renderer::draw(-1, 16, L'\u2560');
			Renderer::draw(93, 16, L'\u2563');
			board->draw();
			break;
		case 4: // AI Win
			Renderer::drawFilledBox(1, 1, GRID_X_WIDTH - 2, GRID_Y_WIDTH - 1, L'-');
			Renderer::drawTextAligned(48, 4, "You lost");
			Renderer::drawTextAligned(48, 12, "Press any key to play again, or hit escape to quit");
			break;
		case 5: // User Win
			Renderer::drawFilledBox(1, 1, GRID_X_WIDTH - 2, GRID_Y_WIDTH - 1, L'+');
			Renderer::drawTextAligned(48, 4, "You Won");
			Renderer::drawTextAligned(48, 12, "Press any key to play again, or hit escape to quit");
			break;
		}

		const ColorScheme outlineScheme = board->playerTurn ? ColorScheme::Highlighted : ColorScheme::AIControl;//State::getState() == 1 ? ColorScheme::Targeted : ColorScheme::Highlighted : ColorScheme::AIControl;
		Renderer::drawBox(0 - Renderer::window[0], 0 - Renderer::window[1], GRID_X_WIDTH - 1 - Renderer::window[0], GRID_Y_WIDTH - 1 - Renderer::window[1], Character(' ', outlineScheme, true));
	});

	/*
	State descriptions:
		0: Start menu
		1: Awaiting playing pick
		2: Placing picked pieces
		3: AI Pick
		4: AI Win
		5: User Win
	*/

	// State machine
	Slot_Scoped<int, int> SlotStateChange = State::SignalStateChange.connect([&](const int& oldState, const int& newState) {
		if (newState < 0) {
			Engine::looping = false;
			return;
		}

		switch (oldState) {
		case 0:
			break;
		case 2:
			board->playerTurn = !board->playerTurn;
			if (newState == 1) {
				int firstIndex = 0;
				for (int i = 0; i < POCKET_WIDTH; i++) {
					if (board->rightPockets.at(i)->getStones()) {
						firstIndex = i;
						break;
					}
				}
				board->selection = POCKET_WIDTH + firstIndex;
			}
			break;
		}

		switch (newState) {
		case 0:
			break;
		case 1:
			// Reset input
			UserInput::clear();
			// Modify rendering view to support border
			Renderer::setWindow(1, 1);
			break;
		case 2:
			Engine::lastTickTime = CHRONO_NOW();
			break;
		case 3:
			// AI pick
			for (int i = 0; i < POCKET_WIDTH; i++) { // AI picks a pocket with stones automatically
				if (board->getPocket(i)->getStones()) {
					board->selection = i;
					break;
				}
			}

			{
				const int targetStones = board->getPocket(board->selection)->getStones();
				if (targetStones) {
					board->getPocket(board->selection)->takeStones(targetStones);
					board->pickedPocket->addStones(targetStones);
					board->selectCCW();
					State::setState(2);
				}
			}
			break;
		case 4: // AI Win
		case 5: // User Win
			Renderer::setWindow(0, 0);
			break;
		}

		Engine::render();
	});

	Slot_Scoped<> SlotTick = Engine::SignalTick.connect([&]() {
		if (board->pickedPocket->getStones()) {
			board->tickSelection();
			if (!board->pickedPocket->getStones()) {
				// Has won?
				int aiFilled = false;
				int userFilled = false;
				for (int i = 0; i < POCKET_WIDTH; i++) {
					if (board->getPocket(i)->getStones()) {
						aiFilled = true;
					}

					if (board->getPocket(i + POCKET_WIDTH)->getStones()) {
						userFilled = true;
					}
				}

				if (!aiFilled) {
					// AI WINS
					State::setState(4);
					return;
				}
				if (!userFilled) {
					// USER WINS
					State::setState(5);
					return;
				}

				if (board->playerTurn) {
					State::setState(3);
				} else {
					State::setState(1);
				}
			}
			Engine::render();
		}
	});

	Slot_Scoped<std::string> SlotTextEntered = UserInput::SignalEntryEntered.connect([&](const std::string& text) {
		
	});

	Slot_Scoped<char> SlotKeyPress = Input::SignalKeyPress.connect([&](const char& key) {
		if (key == Key::Esc) {
			Engine::looping = false;
			return;
		}

		switch (State::getState()) {
		case 0:
			State::setState(1);
			break;
		case 1:
			switch (key) {
			case VK_LEFT:
				board->moveSelection(-1);
				Engine::render();
				break;
			case VK_RIGHT:
				board->moveSelection(1);
				Engine::render();
				break;
			case Key::Return:
				const int targetStones = board->getPocket(board->selection)->getStones();
				if (targetStones) {
					board->getPocket(board->selection)->takeStones(targetStones);
					board->pickedPocket->addStones(targetStones);
					board->selectCCW();
					State::setState(2);
				}
				break;
			}
			break;
		case 4:
		case 5:
			board->setup();
			State::setState(1);
			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}