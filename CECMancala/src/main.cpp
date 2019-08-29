/*
	main.cpp

	Dylan Pozarnsky 8/14/2019

	Hello China
*/

#include <iostream>

#include <Console/Console.h>

#include <Engine.h>

#include <memory>

int main() {
	Engine::init();
	Engine::loop();
	Engine::deinit();

	return 0;
}