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
    Area(std::string name);
    ~Area();

    sf::Vector2i getDimensions();
    std::string& getAreaName();

    void setMapTile(unsigned int x, unsigned int y, std::shared_ptr<Terrain> &terrain);

    void setEntity(int x, int y, const std::shared_ptr<Entity> entity);
    void spawnPlayer(int x, int y, unsigned int hp);

    void despawnPlayer();
    Player passPlayer();

    bool moveEntity(int x, int y, const std::shared_ptr<Entity> &entity);
    bool movePlayer(int xOffset, int yOffset);
    bool movePlayerToThisArea(int xOffset, int yOffset, const std::shared_ptr<Area> &prevArea);

    void draw();
    void genRandom(const unsigned int& seed);

    void setLocationalPosition(sf::Vector2i pos);
    sf::Vector2i getLocationalPosition();

    void resetRenderPos(int x, int y);

    const std::shared_ptr<Player>& getPlayer();

private:
    const std::shared_ptr<Terrain> & getMapTile(int row, int col);

    std::string areaName;

    sf::Vector2i dimensions;
    sf::Vector2i locationalPosition;

    std::vector<std::vector<std::shared_ptr<Terrain>>> map;
    std::vector<std::vector<std::shared_ptr<Entity>>> entityLayer;

    std::shared_ptr<Player> player;
};