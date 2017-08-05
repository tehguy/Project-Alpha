#pragma once

#include "constants.hpp"
#include <memory>

class Graphics {
public:
	Graphics();
	int init();

	std::shared_ptr<sf::RenderWindow>& getWindow();

private:
	std::shared_ptr<sf::RenderWindow> window;
};