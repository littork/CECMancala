#pragma once

#include <Macros.h>

class Renderer {
private:
	Renderer() {};
private:
	static bool initialized;
private:
	static char buffer[GRID_X_WIDTH][GRID_Y_WIDTH];
public:
	static void init();
public:
	static void draw(const unsigned int& x, const unsigned int& y, const char& character);
	static void drawLine(const int& x, const int& y, const int& width, const int& height, const char& character);
public:
	static void flush();
};