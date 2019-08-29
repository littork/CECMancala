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

void Renderer::drawLine(const unsigned int& x, const unsigned int& y, const unsigned int& width, const unsigned int& height, const char& character) {
#ifdef _DEBUG
	if (x > width || y > height || x < 0 || y < 0 || width < 0 || height < 0) {
		throw;
	}
#endif

	const unsigned int dx = width - x;
	const unsigned int dy = height - y;
	const float err = (float) dy / (float) dx;

	if (dx == 0) {
		for (unsigned int _y = y; _y <= height; _y++) {
			draw(x, _y, character);
		}
		return;
	} else if (dy == 0) {
		for (unsigned int _x = x; _x <= width; _x++) {
			draw(_x, y, character);
		}
		return;
	}

	float _y = y;

	for (unsigned int _x = x; _x <= width; _x++) {
		draw(_x, (unsigned int) _y, character);
		_y += err;
		if (_y > height) {
			_y = height - 1;
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