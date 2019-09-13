#include "StoneConfiguration.h"

#include <stdlib.h>
#include "MancalaMacros.h"

StoneConfiguration::StoneConfiguration() : configuration() {
	for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION; y++) {
		for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION; x++) {
			configuration[x + (y * POCKET_INTERNAL_DIMENSION)] = std::make_shared<ConfigurationMapper>();
		}
	}
}

void StoneConfiguration::calculate(const unsigned int& stones) {
	if (stones == 0) {
		for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION; y++) {
			for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION; x++) {
				configuration[x + (y * POCKET_INTERNAL_DIMENSION)]->x = 0;
				configuration[x + (y * POCKET_INTERNAL_DIMENSION)]->y = 0;
			}
		}
	}

	unsigned int counter = 0;

	while (true) {
		unsigned int randX = std::rand() % POCKET_INTERNAL_DIMENSION;
		unsigned int randY = std::rand() % POCKET_INTERNAL_DIMENSION;

		bool duplicate = false;

		// Check for duplicates
		for (unsigned int y = 0; y < POCKET_INTERNAL_DIMENSION; y++) {
			for (unsigned int x = 0; x < POCKET_INTERNAL_DIMENSION; x++) {
				if (configuration[x + (y * POCKET_INTERNAL_DIMENSION)]->x == randX && configuration[x + (y * POCKET_INTERNAL_DIMENSION)]->y == randY) {
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