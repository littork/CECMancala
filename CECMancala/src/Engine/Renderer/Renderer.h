#pragma once

#include <Engine/Macros.h>
#include <string>

class Renderer {
private:
	Renderer() {};
private:
	static bool initialized;
private:
	static char buffer[GRID_X_WIDTH][GRID_Y_WIDTH];
	static char lastBuffer[GRID_X_WIDTH][GRID_Y_WIDTH];
public:
	static void init();
private:
public:
	static void setWindow(const unsigned int& xOffset, const unsigned int& yOffset);
	static unsigned int window[2];
public:
	static void draw(const int& x, const int& y, const char& character);
	static void drawLine(const int& x, const int& y, const int& width, const int& height, const char& character);
	static void drawTextAligned(const int& x, const int& y, const std::string& text);
	static void drawText(const int& x, const int& y, const std::string& text);
	static void drawBox(const int& x, const int& y, const int& x2, const int& y2, const char& character);
	static void drawSmartBox(const int& x, const int& y, const int& x2, const int& y2);
	static void drawFilledBox(const int& x, const int& y, const int& x2, const int& y2, const char& character);
public:
	static void flush();
};