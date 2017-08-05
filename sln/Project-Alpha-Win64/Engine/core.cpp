#include "stdafx.h"
#include "core.hpp"
#include "gfx.hpp"

#include <iostream>

int Core::init() {
	if (!gfx.init()) {
		return 1;
	}

	gameLoop();

	return 0;
}

void Core::gameLoop() {
	gfx.getWindow()->setActive();
	while (gfx.getWindow()->isOpen()) {
		sf::Event event;
		while (gfx.getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gfx.getWindow()->close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				handleInput(event.key.code);
			}
		}
		draw();
	}

	std::cout << "whooo" << std::endl;
}

void Core::handleInput(int key) {
	switch (key) {
	case sf::Keyboard::Q: case sf::Keyboard::Escape:
		gfx.getWindow()->close();
		break;
	default:
		break;
	}
}

void Core::draw() {
	gfx.getWindow()->clear(sf::Color::Black);

	//draw location

	gfx.getWindow()->display();
}
