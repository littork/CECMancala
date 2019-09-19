/*
Console.h

Dylan Pozarnsky

Provides abstraction behind console related functions
*/

#pragma once

#include <iostream>
#include <Windows.h>

class Console {
private:
	Console() {};
public:
	static void init();
private:
	static bool initialized;
public:
	static HANDLE handle;
private:
	static COORD coordZero;
	static COORD activeCoord;
public:
	static void reset();
public:
	/*template<typename T>
	static void write(T v) {
		std::cout << v << std::endl;
	}

	template<typename T, typename... Args>
	static void write(T first, Args... args) {
		std::cout << first;
		log(args...);
	}*/

	template<typename T>
	static void log(T v) {
		std::cout << v << "\n";
	}

	template<typename T, typename... Args>
	static void log(T first, Args... args) {
		std::cout << first;
		log(args...);
	}

	static void setCursorVisible(const bool& visible);
	static void setCursorPosition(const unsigned int& x, const unsigned int& y);
	static void setTextAttribute(const char& attribute);
};