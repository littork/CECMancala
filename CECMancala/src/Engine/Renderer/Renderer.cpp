#include "Renderer.h"

#include <Engine/Console/Console.h>
#include <math.h>

#include <io.h>
#include <fcntl.h>

bool Renderer::initialized = false;
Character Renderer::buffer[GRID_X_WIDTH][GRID_Y_WIDTH] = {};
Character Renderer::lastBuffer[GRID_X_WIDTH][GRID_Y_WIDTH] = {};

unsigned int Renderer::window[2] = {0, 0};

void Renderer::init() {
	if (initialized) {
		return;
	}

	initialized = true;

	_setmode(_fileno(stdout), _O_U16TEXT);

	for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
		for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
			buffer[x][y] = Character();
		}
	}
}

void Renderer::setWindow(const unsigned int& xOffset, const unsigned int& yOffset) {
	window[0] = xOffset;
	window[1] = yOffset;
}

void Renderer::draw(const int& x, const int& y, const Character& character) {
#ifdef _DEBUG
	if (x + window[0] >= GRID_X_WIDTH || y + window[1] >= GRID_Y_WIDTH || x + window[0] < 0 || y + window[1] < 0) {
		throw;
		return;
	}
#endif

	if (!character.paint) {
		buffer[x + window[0]][y + window[1]] = character;
	} else {
		buffer[x + window[0]][y + window[1]].scheme = character.scheme;
	}
}
void Renderer::drawBox(const int& x, const int& y, const int& x2, const int& y2, const Character& character) {
#ifdef _DEBUG
	if (x2 < x || y2 < y) {
		throw;
		return;
	}
#endif

	Renderer::drawLine(x, y, x2, y, character);
	Renderer::drawLine(x, y, x, y2, character);
	Renderer::drawLine(x, y2, x2, y2, character);
	Renderer::drawLine(x2, y, x2, y2, character);
}
void Renderer::drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const Character& character) {
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
void Renderer::drawLine(const int& x, const int& y, const int& x2, const int& y2, const Character& character) {
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

void Renderer::draw(const int& x, const int& y, const wchar_t& character) {
	draw(x, y, Character(character));
}
void Renderer::drawBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
	drawBox(x, y, x2, y2, Character(character));
}
void Renderer::drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
	drawFilledBox(x, y, x2, y2, Character(character));
}
void Renderer::drawLine(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character) {
	drawLine(x, y, x2, y2, Character(character));
}

void Renderer::drawSmartBox(const int& x, const int& y, const int& x2, const int& y2, const ColorScheme& color) {
#ifdef _DEBUG
	if (x2 < x || y2 < y) {
		throw;
		return;
	}
#endif

	/*
		https://www.fileformat.info/info/unicode/block/box_drawing/list.htm
	*/

	Renderer::drawLine(x, y, x, y2, Character(L'\u2551', color));
	Renderer::drawLine(x2, y, x2, y2, Character(L'\u2551', color));
	Renderer::drawLine(x, y2, x2, y2, Character(L'\u2550', color));
	Renderer::drawLine(x, y, x2, y, Character(L'\u2550', color));

	Renderer::draw(x, y, Character(L'\u2554', color));
	Renderer::draw(x2, y, Character(L'\u2557', color));
	Renderer::draw(x, y2, Character(L'\u255a', color));
	Renderer::draw(x2, y2, Character(L'\u255d', color));
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
void Renderer::setColorScheme(const ColorScheme& scheme) {
	switch (scheme) {
	case ColorScheme::White:
		Console::setTextAttribute(15);
		break;
	case ColorScheme::AI:
		Console::setTextAttribute(12);
		break;
	case ColorScheme::AIControl:
		Console::setTextAttribute(12);
		break;
	case ColorScheme::Player:
		Console::setTextAttribute(7);
		break;
	case ColorScheme::Highlighted:
		Console::setTextAttribute(14);
		break;
	case ColorScheme::Targeted:
		Console::setTextAttribute(10);
		break;
	default:
		break;
	}
}

void Renderer::flush() {
	for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
		for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
			//if (buffer[x][y] == lastBuffer[x][y]) {
			//	SetCursorPos(x + 1, y);
			//} else {
			Renderer::setColorScheme(buffer[x][y].scheme);
			std::wcout << buffer[x][y].character;
			Renderer::setColorScheme(ColorScheme::White);
			//}
		}
		std::wcout << L"\n";
	}

	for (unsigned int x = 0; x < GRID_X_WIDTH; x++) {
		for (unsigned int y = 0; y < GRID_Y_WIDTH; y++) {
			//lastBuffer[x][y] = buffer[x][y];
			buffer[x][y].character = ' ';
			buffer[x][y].scheme = ColorScheme::White;
		}
	}
}