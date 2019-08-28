#pragma once

#include <iostream>

class Console {
private:
	Console() {};
public:
	static void clear();
public:
	template<typename T>
	static void write(T v) {
		std::cout << v << std::endl;
	}

	template<typename T, typename... Args>
	static void write(T first, Args... args) {
		std::cout << first;
		log(args...);
	}

	template<typename T>
	static void log(T v) {
		std::cout << v << "\n";
	}

	template<typename T, typename... Args>
	static void log(T first, Args... args) {
		std::cout << first;
		log(args...);
	}
};