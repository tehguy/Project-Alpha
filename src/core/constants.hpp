/*
    Project Alpha
    Copyright (C) 2017  tehguy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class CONSTANTS {
public:
    static CONSTANTS& GET_OBJECT() {
        static CONSTANTS instance;
        return instance;
    };

    CONSTANTS(CONSTANTS const&) = delete;
    void operator=(CONSTANTS const&) = delete;

    const int TILE_WIDTH = 16;
    const int TILE_HEIGHT = 16;

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    const int AREA_WIDTH = 20;
    const int AREA_HEIGHT = 20;

    const sf::Rect<int> BLANK_SPRITE_RECT = sf::Rect<int>(0, 0, 0, 0);
    const sf::Rect<int> GRASS_SPRITE_RECT = sf::Rect<int>(0, 0, TILE_WIDTH, TILE_HEIGHT);
    const sf::Rect<int> WATER_SPRITE_RECT = sf::Rect<int>(16, 0, TILE_WIDTH, TILE_HEIGHT);
    const sf::Rect<int> MOUNTAIN_SPRITE_RECT = sf::Rect<int>(32, 0, TILE_WIDTH, TILE_HEIGHT);
    const sf::Rect<int> SNOW_SPRITE_RECT = sf::Rect<int>(48, 0, TILE_WIDTH, TILE_HEIGHT);
    const sf::Rect<int> PLAYER_SPRITE_RECT = sf::Rect<int>(0, 16, TILE_WIDTH, TILE_HEIGHT);
    const sf::Rect<int> CURSOR_SPRITE_RECT = sf::Rect<int>(16, 16, TILE_WIDTH, TILE_HEIGHT);

private:
    CONSTANTS() = default;
};