#include "Hole.h"

#include <Engine/Renderer/Renderer.h>

#include <Mancala/MancalaMacros.h>

unsigned int Hole::getStones() {
	return this->stones;
}

void Hole::addStones(const unsigned int& amount) {
	this->stones += amount;
}

unsigned int Hole::takeStones(const unsigned int& amount) {
	const unsigned int originalStones = this->stones;
	this->stones -= amount;
	if (this->stones < 0) {
		this->stones = 0;
	}
	return originalStones - this->stones;
}

void Hole::drawPocket(const unsigned int& x, const unsigned int& y) {
	// Renderer::draw(2 * x, y, '+');
	Renderer::drawBox(12 * x + POCKETS_X_OFFSET, y * 10, (12 * x) + 8 + POCKETS_X_OFFSET, (y * 10) + 5, '+');
}