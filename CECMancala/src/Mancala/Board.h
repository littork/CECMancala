#pragma once

#include <memory>
#include <vector>

#include "Hole.h"

class Board {
public:
	Board() : 
		leftMancala(nullptr),
		rightMancala(nullptr),
		leftPockets(std::vector<std::shared_ptr<Hole>>()),
		rightPockets(std::vector<std::shared_ptr<Hole>>()),
		selection(0),
		playerTurn(true),
		activeStones(0)
	{};
public:
	std::shared_ptr<Hole> leftMancala;
	std::shared_ptr<Hole> rightMancala;

	std::vector<std::shared_ptr<Hole>> leftPockets;
	std::vector<std::shared_ptr<Hole>> rightPockets;
public:
	std::shared_ptr<Hole> getPocket(const int& position);
public:
	bool playerTurn;
	int activeStones;
public:
	int selection;
	void moveSelection(const int& change);
	void selectCCW();
public:
	void setup();
	void draw();
};