#pragma once

#include <memory>
#include <vector>

class Hole;

class Board {
public:
	Board() : 
		leftMancala(nullptr),
		rightMancala(nullptr),
		leftPockets(std::vector<std::shared_ptr<Hole>>()),
		rightPockets(std::vector<std::shared_ptr<Hole>>())
	{};
public:
	std::shared_ptr<Hole> leftMancala;
	std::shared_ptr<Hole> rightMancala;

	std::vector<std::shared_ptr<Hole>> leftPockets;
	std::vector<std::shared_ptr<Hole>> rightPockets;
public:
	void setup();
	void draw();
};