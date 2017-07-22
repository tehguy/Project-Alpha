/*
    CPPAdventures
    Copyright (C) 2017  TehGuy

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
#include <string>
#include <vector>

#include <include/entity/player.hpp>

#include <include/world/terrain/terrain.hpp>

class Area {
public:
    Area(std::string name, unsigned int _width, unsigned int _height);
    ~Area();

    sf::Vector2i getDimensions();
    std::string& getAreaName();

    void setMapTile(unsigned int x, unsigned int y, Terrain* terrain);

    void setEntity(int x, int y, Entity *entity);
    void spawnPlayer(int x, int y, unsigned int hp);

    bool moveEntity(int x, int y, Entity& entity);
    void movePlayer(int xOffset, int yOffset);

    void draw();
    void genRandom(const unsigned int& seed);

    void setLocationalPosition(sf::Vector2i pos);
    sf::Vector2i getLocationalPosition();

private:
    const std::shared_ptr<Terrain> getMapTile(int row, int col);

    std::string areaName;

    sf::Vector2i dimensions;
    sf::Vector2i locationalPosition;

    std::vector<std::vector<std::shared_ptr<Terrain>>> map;
    std::vector<std::vector<Entity*>> entityLayer;

    std::shared_ptr<Player> player;
};