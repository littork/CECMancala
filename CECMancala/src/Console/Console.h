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
private:
	static HANDLE handle;
	static COORD coordZero;
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
};