#include "Board.h"

#include "Hole.h"

#include "MancalaMacros.h"

void Board::setup() {
	// Create board
	leftMancala = std::make_shared<Hole>();
	rightMancala = std::make_shared<Hole>();

	for (unsigned int i = 0; i < POCKET_WIDTH; i++) {
		leftPockets.push_back(std::make_shared<Hole>());
		rightPockets.push_back(std::make_shared<Hole>());
	}

	// Place pieces
	for (unsigned int i = 0; i < POCKET_WIDTH; i++) {
		leftPockets[i]->addStones(POCKET_STARTING_STONES);
		rightPockets[i]->addStones(POCKET_STARTING_STONES);
	}

	selection = POCKET_WIDTH; // User takes first turn
}

void Board::draw() {
	leftMancala->drawMancala(0, selection == POCKET_WIDTH * 2);
	rightMancala->drawMancala(1, selection == POCKET_WIDTH * 2 + 1);

	for (unsigned int x = 0; x < POCKET_WIDTH; x++) {
		leftPockets[x]->drawPocket(x, 0, selection == x);
		rightPockets[x]->drawPocket(x, 1, selection == x + POCKET_WIDTH);
	}
}

void Board::moveSelection(const int& change) {
	if (selection + change >= POCKET_WIDTH) {
		if (selection + change < POCKET_WIDTH * 2 - 1) {
			selection += change;
		} else {
			selection = POCKET_WIDTH * 2 - 1;
		}
	} else {
		selection = POCKET_WIDTH;
	}
}
std::shared_ptr<Hole> Board::getPocket(const int& position) {
#ifdef _DEBUG
	if (position < 0 || position >= POCKET_WIDTH * 2) {
		throw;
	}
#endif

	if (position < POCKET_WIDTH) {
		return leftPockets.at(position);
	} else {
		return rightPockets.at(position - POCKET_WIDTH);
	}
}

void Board::selectCCW() {
	if (selection < POCKET_WIDTH) {
		selection--;
	} else {
		selection++;
	}

	if (selection == POCKET_WIDTH * 2) {
		selection = POCKET_WIDTH * 2 + 1;
	} else if (selection == POCKET_WIDTH * 2 + 2) {
		selection = POCKET_WIDTH - 1;
	} else if (selection == -1) {
		selection = POCKET_WIDTH * 2;
	} else if (selection == POCKET_WIDTH * 2 + 1) {
		selection = POCKET_WIDTH;
	}
}