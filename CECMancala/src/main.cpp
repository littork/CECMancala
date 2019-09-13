/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Rock Paper Scissors Project

	The engine is very incomplete.
*/

#include <Engine/Engine_Core.h>

#include <cstdlib>
#include <memory>

#include <Mancala/Board.h>

int main() {
	Engine::init();

	std::shared_ptr<Board> board = std::make_shared<Board>();
	board->setup();

	// Renderer
	Slot_Scoped<> SlotRender = Engine::SignalRender.connect([&]() {
		Renderer::drawSmartBox(0 - Renderer::window[0], 0 - Renderer::window[1], GRID_X_WIDTH - 1 - Renderer::window[0], GRID_Y_WIDTH - 1 - Renderer::window[1]);

		switch (State::getState()) {
		case 0:
			Renderer::drawFilledBox(1, 1, GRID_X_WIDTH - 2, GRID_Y_WIDTH - 1, '.');
			Renderer::drawTextAligned(48, 4, "CEC Mancala");
			Renderer::drawTextAligned(48, 6, "By Dylan Pozarnsky");
			Renderer::drawTextAligned(48, 12, "Press any key to begin");
			break;
		case 1:
			board->draw();
			Renderer::drawLine(0, 16, 92, 16, '=');
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
		case 1:
			// Reset input
			UserInput::clear();
			// Modify rendering view to support border
			Renderer::setWindow(1, 1);
			break;
		}

		Engine::render();
	});

	Slot_Scoped<std::string> SlotTextEntered = UserInput::SignalEntryEntered.connect([&](const std::string& text) {
		
	});

	Slot_Scoped<char> SlotKeyPress = Input::SignalKeyPress.connect([&](const char& key) {
		switch (State::getState()) {
		case 0:
			State::setState(1);
			break;
		}
	});

	Engine::loop();
	Engine::deinit();

	return 0;
}