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
}

void Board::draw() {
	leftMancala->drawMancala(0);
	rightMancala->drawMancala(1);

	for (unsigned int x = 0; x < POCKET_WIDTH; x++) {
		leftPockets[x]->drawPocket(x, 0);
		rightPockets[x]->drawPocket(x, 1);
	}
}