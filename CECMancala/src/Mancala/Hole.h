#pragma once

#include "StoneConfiguration.h"

#include <memory>

class Hole {
public:
	Hole() : stones(0), stoneConfiguration(std::make_shared<StoneConfiguration>()) {};
private:
	unsigned int stones;
	std::shared_ptr<StoneConfiguration> stoneConfiguration;
public:
	unsigned int getStones();
	void addStones(const unsigned int& amount = 1);

	/*
		takeStones

		Takes given number of stones from hole, if there are not enough stones
		to meet take demand the number of stones that were taken is returned
	*/
	unsigned int takeStones(const unsigned int& amount = 1);
public:
	void drawPocket(const unsigned int& x, const unsigned int& y, const bool& highlighted = false);
	void drawMancala(const unsigned int& x, const bool& highlighted = false);
	void drawPickedPocket();
};