#include "Hole.h"

#include <Engine/Renderer/Renderer.h>
#include <Mancala/MancalaMacros.h>

#include <Engine/State.h>

unsigned int Hole::getStones() {
	return this->stones;
}

void Hole::addStones(const unsigned int& amount) {
	this->stones += amount;
	this->recalculateStoneConfiguration();
}

void Hole::recalculateStoneConfiguration() {
	this->stoneConfiguration->calculate(this->stones);
}

unsigned int Hole::takeStones(const unsigned int& amount) {
	const unsigned int originalStones = this->stones;
	this->stones -= amount;
	if (this->stones < 0) {
		this->stones = 0;
	}
	return originalStones - this->stones;
	this->recalculateStoneConfiguration();
}

void Hole::drawPocket(const unsigned int& x, const unsigned int& y, const bool& highlighted) {
	// Renderer::draw(2 * x, y, '+');
	Renderer::drawBox(12 * x + POCKETS_X_OFFSET, y * 10, (12 * x) + 8 + POCKETS_X_OFFSET, (y * 10) + 5, Character(L'\u2588', highlighted ? State::getState() == 1 ? ColorScheme::Highlighted : ColorScheme::Targeted : y ? ColorScheme::Player : ColorScheme::AI));

	for (unsigned int i = 0; i < this->stones; i++) {
		Renderer::draw(12 * x + POCKETS_X_OFFSET + this->stoneConfiguration->configuration[i]->x + 1, y * 10 + this->stoneConfiguration->configuration[i]->y + 1, L'\u058d');
	}


}

void Hole::drawMancala(const unsigned int& x, const bool& highlighted) {
	Renderer::drawBox(84 * x, 0, 84 * x + 8, 15, Character(L'\u2588', highlighted ? ColorScheme::Targeted : x ? ColorScheme::AI : ColorScheme::Player));
}