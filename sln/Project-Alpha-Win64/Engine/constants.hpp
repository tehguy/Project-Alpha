#pragma once

#include <SFML/Graphics.hpp>

namespace CONSTANTS {
	const int TILE_WIDTH = 16;
	const int TILE_HEIGHT = 16;

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int AREA_WIDTH = 50;
	const int AREA_HEIGHT = 50;

	const sf::Rect<int> BLANK_SPRITE_RECT = sf::Rect<int>(0, 0, 0, 0);
	const sf::Rect<int> GRASS_SPRITE_RECT = sf::Rect<int>(0, 0, TILE_WIDTH, TILE_HEIGHT);
	const sf::Rect<int> WATER_SPRITE_RECT = sf::Rect<int>(16, 0, TILE_WIDTH, TILE_HEIGHT);
	const sf::Rect<int> MOUNTAIN_SPRITE_RECT = sf::Rect<int>(32, 0, TILE_WIDTH, TILE_HEIGHT);
	const sf::Rect<int> SNOW_SPRITE_RECT = sf::Rect<int>(48, 0, TILE_WIDTH, TILE_HEIGHT);
	const sf::Rect<int> PLAYER_SPRITE_RECT = sf::Rect<int>(0, 16, TILE_WIDTH, TILE_HEIGHT);
	const sf::Rect<int> CURSOR_SPRITE_RECT = sf::Rect<int>(16, 16, TILE_WIDTH, TILE_HEIGHT);
}