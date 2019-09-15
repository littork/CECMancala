#include "StoneConfiguration.h"

#include <stdlib.h>
#include "MancalaMacros.h"

StoneConfiguration::StoneConfiguration() : configuration() {
	for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION_Y; y++) {
		for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION_X; x++) {
			configuration[x + (y * POCKET_INTERNAL_DIMENSION_X)] = std::make_shared<ConfigurationMapper>();
		}
	}

	calculate(POCKET_INTERNAL_DIMENSION_X * POCKET_INTERNAL_DIMENSION_Y - 1);
}

void StoneConfiguration::calculate(const unsigned int& stones) {
#ifdef _DEBUG
	if (stones > (POCKET_INTERNAL_DIMENSION_X * POCKET_INTERNAL_DIMENSION_Y)) {
		throw; // You can't fit more than this number of stones in one pocket
		return;
	}
#endif

	if (stones == 0) {
		for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION_Y; y++) {
			for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION_X; x++) {
				configuration[x + (y * POCKET_INTERNAL_DIMENSION_X)]->x = 0;
				configuration[x + (y * POCKET_INTERNAL_DIMENSION_X)]->y = 0;
			}
		}
	}

	unsigned __int16 counter = 0;

	while (true) {
		unsigned int randX = std::rand() % POCKET_INTERNAL_DIMENSION_X;
		unsigned int randY = std::rand() % POCKET_INTERNAL_DIMENSION_Y;

		bool duplicate = false;

		// Check for duplicates
		for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION_Y; y++) {
			for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION_X; x++) {
				if (configuration[x + (y * POCKET_INTERNAL_DIMENSION_X)]->x == randX && configuration[x + (y * POCKET_INTERNAL_DIMENSION_X)]->y == randY) {
					duplicate = true;
					break;
				}
			}

			if (duplicate) {
				break;
			}
		}
		if (duplicate) {
			continue;
		}

		configuration[counter]->x = randX;
		configuration[counter]->y = randY;

		counter++;

		if (counter >= stones) {
			break;
		}
	}
}