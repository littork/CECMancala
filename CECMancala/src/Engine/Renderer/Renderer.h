#pragma once

#include <Engine/Macros.h>
#include <string>

enum class ColorScheme {
	White,
	AI,
	Player,
	Highlighted,
	Targeted
};

struct Character {
	Character(const wchar_t& _character = ' ', const ColorScheme& _scheme = ColorScheme::White) {
		character = _character;
		scheme = _scheme;
	}

	wchar_t character;
	ColorScheme scheme;

};

class Renderer {
private:
	Renderer() {};
private:
	static bool initialized;
private:
	static Character buffer[GRID_X_WIDTH][GRID_Y_WIDTH];
	static Character lastBuffer[GRID_X_WIDTH][GRID_Y_WIDTH];
public:
	static void init();
private:
public:
	static void setWindow(const unsigned int& xOffset, const unsigned int& yOffset);
	static unsigned int window[2];
public:
	static void drawTextAligned(const int& x, const int& y, const std::string& text);
	static void drawText(const int& x, const int& y, const std::string& text);
	static void drawSmartBox(const int& x, const int& y, const int& x2, const int& y2);
public:
	static void draw(const int& x, const int& y, const Character& character);
	static void drawLine(const int& x, const int& y, const int& width, const int& height, const Character& character);
	static void drawBox(const int& x, const int& y, const int& x2, const int& y2, const Character& character);
	static void drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const Character& character);
public:
	static void draw(const int& x, const int& y, const wchar_t& character);
	static void drawLine(const int& x, const int& y, const int& width, const int& height, const wchar_t& character);
	static void drawBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character);
	static void drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const wchar_t& character);
public:
	static void setColorScheme(const ColorScheme& scheme);
public:
	static void flush();
};