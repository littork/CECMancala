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
	std::shared_ptr<Engine> engine = std::make_shared<Engine>();
	engine->loop();

	return 0;
}