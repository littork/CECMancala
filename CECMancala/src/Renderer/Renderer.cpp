#include "Renderer.h"

#include <Console/Console.h>
#include <math.h>

bool Renderer::initialized = false;
char Renderer::buffer[GRID_X_WIDTH][GRID_Y_WIDTH] = { 0 };

void Renderer::init() {
	if (initialized) {
		return;
	}

	initialized = true;
}

void Renderer::draw(const unsigned int& x, const unsigned int& y, const char& character) {
#ifdef _DEBUG
	if (x >= GRID_X_WIDTH || y >= GRID_Y_WIDTH || x < 0 || y < 0) {
		throw;
	}
#endif

	buffer[x][y] = character;
}

void Renderer::drawLine(const int& x, const int& y, const int& x2, const int& y2, const char& character) {
#ifdef _DEBUG
	if (x < 0 || y < 0 || x2 < 0 || y2 < 0) {
		throw;
	}
#endif

	const int dx = (int) x2 - (int) x;
	const int dy = (int) y2 - (int) y;
	const float err = abs((float) dy / (float) dx);

	if (dx == 0) {
		for (int _y = y; _y <= y2; _y++) {
			draw(x, _y, character);
		}
		return;
	} else if (dy == 0) {
		for (int _x = x; _x <= x2; _x++) {
			draw(_x, y, character);
		}
		return;
	}

	float _y = abs((float) y);

	for (int _x = x; (x2 > x ? (_x < x2) : (_x >= x2)); x2 > x ? _x++ : _x--) {
		draw(_x, (int) _y, character);
		_y += err;
		if (_y > y2) {
			_y = abs((float) y2 - (float) 1);
		}
	}
}

void Renderer::flush() {
	for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
		for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
			std::cout << buffer[x][y];
		}
		std::cout << "\n";
	}

	for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
		for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
			buffer[x][y] = 0;
		}
	}
}