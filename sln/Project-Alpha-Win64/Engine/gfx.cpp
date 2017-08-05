#include "stdafx.h"
#include "gfx.hpp"

Graphics::Graphics() {}

int Graphics::init() {
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "Test"));

	return true;
}

std::shared_ptr<sf::RenderWindow>& Graphics::getWindow() {
	return window;
}
