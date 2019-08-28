#include "Renderer.h"

#include <Console/Console.h>

bool Renderer::initialized = false;
char Renderer::buffer[32][32] = { 0 };

void Renderer::init() {
	if (initialized) {
		return;
	}

	initialized = true;
}

void Renderer::draw(const unsigned __int8& x, const unsigned __int8& y) {
	
}

void Renderer::flush() {

}