/*
ConfigurationMapper.h

Dylan Pozarnsky

Helps visually map mancala pieces into pockets
*/

#pragma once

struct ConfigurationMapper {
	ConfigurationMapper() : x(0), y(0) {}

	int x;
	int y;
};