#pragma once

class Hole {
public:
	Hole() : stones(0) {};
private:
	unsigned int stones;
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
	void drawPocket(const unsigned int& x, const unsigned int& y);
};