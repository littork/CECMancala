#include "Renderer.h"

#include <Engine/Console/Console.h>
#include <math.h>

#include <io.h>
#include <fcntl.h>

bool Renderer::initialized = false;
wchar_t Renderer::buffer[GRID_X_WIDTH][GRID_Y_WIDTH] = { 0 };
wchar_t Renderer::lastBuffer[GRID_X_WIDTH][GRID_Y_WIDTH] = { 0 };

unsigned int Renderer::window[2] = {0, 0};

void Renderer::init() {
	if (initialized) {
		return;
	}

	initialized = true;

	_setmode(_fileno(stdout), _O_U16TEXT);
}

void Renderer::setWindow(const unsigned int& xOffset, const unsigned int& yOffset) {
	window[0] = xOffset;
	window[1] = yOffset;
}

void Renderer::draw(const int& x, const int& y, const wchar_t& character) {
#ifdef _DEBUG
	if (x + window[0] >= GRID_X_WIDTH || y + window[1] >= GRID_Y_WIDTH || x + window[0] < 0 || y + window[1] < 0) {
		throw;
		return;
	}
#endif

	buffer[x + window[0]][y + window[1]] = character;
}

void Renderer::drawBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
#ifdef _DEBUG
	if (x < 0 || y < 0 || x2 < 0 || y2 < 0 || x2 < x || y2 < y) {
		throw;
		return;
	}
#endif

	Renderer::drawLine(x, y, x2, y, character);
	Renderer::drawLine(x, y, x, y2, character);
	Renderer::drawLine(x, y2, x2, y2, character);
	Renderer::drawLine(x2, y, x2, y2, character);
}

void Renderer::drawSmartBox(const int& x, const int& y, const int& x2, const int& y2) {
#ifdef _DEBUG
	if (x2 < x || y2 < y) {
		throw;
		return;
	}
#endif

	/*
		https://www.fileformat.info/info/unicode/block/box_drawing/list.htm
	*/

	Renderer::drawLine(x, y, x, y2, L'\u2551');
	Renderer::drawLine(x2, y, x2, y2, L'\u2551');
	Renderer::drawLine(x, y2, x2, y2, L'\u2550');
	Renderer::drawLine(x, y, x2, y, L'\u2550');

	Renderer::draw(x, y, L'\u2554');
	Renderer::draw(x2, y, L'\u2557');
	Renderer::draw(x, y2, L'\u255a');
	Renderer::draw(x2, y2, L'\u255d');
}

void Renderer::drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
#ifdef _DEBUG
	if (x < 0 || y < 0 || x2 < 0 || y2 < 0 || x2 < x || y2 < y) {
		throw;
		return;
	}
#endif

	for (int i = y; i < y2; i++) {
		Renderer::drawLine(x, i, x2, i, character);
	}
}

void Renderer::drawLine(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
#ifdef _DEBUG
	if (x2 < x || y2 < y) {
		throw;
		return;
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

void Renderer::drawTextAligned(const int& x, const int& y, const std::string& text) {
	drawText(x - (unsigned int) (((float) text.length()) / 2.f), y, text);
}

void Renderer::drawText(const int& x, const int& y, const std::string& text) {
#ifdef _DEBUG
	if (x + text.length() >= (GRID_X_WIDTH * GRID_Y_WIDTH)) {
		throw;
		return;
	}
#endif

	for (int _y = y; _y < y + ceilf((float) text.length() / (float) GRID_X_WIDTH); _y++) {
		for (int _x = x; _x < (text.length() + x < GRID_X_WIDTH ? text.length() + x : (min(text.length() - ((_y - y) * GRID_X_WIDTH), GRID_X_WIDTH))); _x++) {
			unsigned int wrapOffset = (_y - y) * GRID_X_WIDTH;
			draw(_x, _y, text.at(_x - x + ((_y - y) ? wrapOffset : 0)));
		}
	}
}

void Renderer::flush() {
	for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
		for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
			//if (buffer[x][y] == lastBuffer[x][y]) {
			//	SetCursorPos(x + 1, y);
			//} else {
				std::wcout << buffer[x][y];
			//}
		}
		std::wcout << L"\n";
	}

	for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
		for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
			//lastBuffer[x][y] = buffer[x][y];
			buffer[x][y] = 0;
		}
	}
}