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

#include <string>
#include <SFML/System.hpp>
#include <utility>
#include <vector>
#include "tile.hpp"

class Area {
public:
    explicit Area(std::string name);

    sf::Vector2i getAreaDimensions() const;
    std::string & getAreaName();

    void drawArea();

    void genRandom(unsigned int seed);

    bool collisionExistsAtPoint(unsigned int x, unsigned int y);

    void resetRenderPos(int x, int y);

private:
    void setMapTile(unsigned int x, unsigned int y, const Tile &tile);
    Tile & getMapTile(unsigned int x, unsigned int y);

    std::string areaName;

    sf::Vector2i areaDimensions;


    std::vector<std::vector<Tile>> tileMap;
};