#pragma once

#include "MancalaMacros.h"

#include <memory>

#include "ConfigurationMapper.h"

class StoneConfiguration {
public:
	StoneConfiguration();
public:
	std::shared_ptr<ConfigurationMapper> configuration[POCKET_INTERNAL_DIMENSION_X * POCKET_INTERNAL_DIMENSION_Y];
public:
	void calculate(const unsigned int& stones);
};