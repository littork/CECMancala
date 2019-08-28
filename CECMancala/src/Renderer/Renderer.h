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
	static void draw(const unsigned __int8& x, const unsigned __int8& y);
public:
	static void flush();
};