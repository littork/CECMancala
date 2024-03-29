/*
Board.h

Dylan Pozarnsky

Basic board structure
*/

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
		pickedPocket(nullptr),
		selection(0),
		playerTurn(true)
	{};
public:
	std::shared_ptr<Hole> leftMancala;
	std::shared_ptr<Hole> rightMancala;

	std::vector<std::shared_ptr<Hole>> leftPockets;
	std::vector<std::shared_ptr<Hole>> rightPockets;

	std::shared_ptr<Hole> pickedPocket;
public:
	std::shared_ptr<Hole> getPocket(const int& position);
public:
	bool playerTurn;
public:
	int selection;
	void moveSelection(const int& change);
	void selectCCW();
public:
	void tickSelection();
public:
	void setup();
	void draw();
};