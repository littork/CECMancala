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

	pickedPocket = std::make_shared<Hole>();

	selection = POCKET_WIDTH; // User takes first turn
}

void Board::draw() {
	leftMancala->drawMancala(0, selection == POCKET_WIDTH * 2);
	rightMancala->drawMancala(1, selection == POCKET_WIDTH * 2 + 1);

	for (unsigned int x = 0; x < POCKET_WIDTH; x++) {
		leftPockets[x]->drawPocket(x, 0, selection == x);
		rightPockets[x]->drawPocket(x, 1, selection == x + POCKET_WIDTH);
	}

	pickedPocket->drawPickedPocket();
}
void Board::tickSelection() {
	if (pickedPocket->getStones()) {
		std::shared_ptr<Hole> resultantPocket = getPocket(selection);
		if (resultantPocket != nullptr) {
			pickedPocket->takeStones(1);
			resultantPocket->addStones(1);

			if (pickedPocket->getStones()) {
				selectCCW();
			} else {
				// Last drop
				if (selection >= POCKET_WIDTH * 2) { // If was in mancala
					playerTurn = !playerTurn; // Extra turn
				} else {
					if (playerTurn && selection >= POCKET_WIDTH && getPocket(selection)->getStones() == 1) { // Last drop is in empty pocket on owning side
						leftMancala->addStones(getPocket(selection - POCKET_WIDTH)->takeStones(-1)); // Take all stones from opposite side and credit them to mancala

						resultantPocket->takeStones(1);
						leftMancala->addStones(1);
					} else if (!playerTurn && selection < POCKET_WIDTH && getPocket(selection)->getStones() == 1) {
						rightMancala->addStones(getPocket(selection + POCKET_WIDTH)->takeStones(-1)); // Take all stones from opposite side and credit them to mancala

						resultantPocket->takeStones(1);
						rightMancala->addStones(1);
					}
				}
			}
		} else {
			selectCCW();
		}

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
	if (position < 0 || position > POCKET_WIDTH * 2 + 1) {
		throw;
	}
#endif

	if (position >= POCKET_WIDTH * 2) {
		if (position == POCKET_WIDTH * 2 && playerTurn) {
			return leftMancala;
		} else if(!playerTurn && position == POCKET_WIDTH * 2 + 1) {
			return rightMancala;
		} else {
			return nullptr;
		}
	}

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