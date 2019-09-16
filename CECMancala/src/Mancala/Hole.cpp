#include "Hole.h"

#include <Engine/Renderer/Renderer.h>
#include <Mancala/MancalaMacros.h>

#include <Engine/State.h>

unsigned int Hole::getStones() {
	return this->stones;
}

void Hole::addStones(const unsigned int& amount) {
	this->stones += amount;
}

unsigned int Hole::takeStones(const int& amount) {
	const unsigned int originalStones = this->stones;
	if (amount == -1) {
		this->stones = 0;
		return originalStones;
	}

	this->stones -= amount;
	if (this->stones < 0) {
		this->stones = 0;
	}
	return originalStones - this->stones;
}

void Hole::drawPocket(const unsigned int& x, const unsigned int& y, const bool& highlighted) {
	// Renderer::draw(2 * x, y, '+');
	Renderer::drawBox(12 * x + POCKETS_X_OFFSET, y * 10, (12 * x) + 8 + POCKETS_X_OFFSET, (y * 10) + 5, Character(L'\u2588', highlighted ? State::getState() == 1 ? ColorScheme::Highlighted : ColorScheme::Targeted : y ? ColorScheme::Player : ColorScheme::AI));

	for (unsigned int i = 0; i < this->stones; i++) {
		Renderer::draw(12 * x + POCKETS_X_OFFSET + this->stoneConfiguration->configuration[i]->x + 1, y * 10 + this->stoneConfiguration->configuration[i]->y + 1, MANCALA_CHARACTER);
	}
}

void Hole::drawMancala(const unsigned int& x, const bool& highlighted) {
	Renderer::drawBox(84 * x, 0, 84 * x + 8, 15, Character(L'\u2588', highlighted ? ColorScheme::Targeted : x ? ColorScheme::AI : ColorScheme::Player));

	for (unsigned int i = 0; i < this->stones; i++) {
		Renderer::draw((84 * x + 1) + ((i / 2) % 6) + ((i / 2) % 6 >= 3 ? 1 : 0), (1 + i % 2) + ((i / 12) * 3), MANCALA_CHARACTER);
	}
}

void Hole::drawPickedPocket() {
	Renderer::drawSmartBox(-1, 16, 31, 18);
	Renderer::draw(31, 16, L'\u2566');
	Renderer::draw(-1, 16, L'\u2560');
	Renderer::draw(-1, 18, L'\u2560');

	for (unsigned int i = 0; i < this->stones; i++) {
		Renderer::draw(i, 17, MANCALA_CHARACTER);
	}
}