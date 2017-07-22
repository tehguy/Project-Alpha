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

#include <include/core/perlinnoise.hpp>

#include <include/gfx/gfx.hpp>

#include <include/world/area.hpp>
#include <include/world/terrain/grass.hpp>
#include <include/world/terrain/snow.hpp>
#include <include/world/terrain/mountain.hpp>
#include <include/world/terrain/water.hpp>

Area::Area(std::string name, unsigned int _width, unsigned int _height) {
    areaName = name;
    dimensions.x = _width;
    dimensions.y = _height;

    player = std::shared_ptr<Player>(nullptr);

    for(unsigned int i = 0; i < dimensions.x; i++){
        map.push_back(std::vector<std::shared_ptr<Terrain>>());
        map.at(i).reserve((unsigned long) dimensions.y);

        entityLayer.push_back(std::vector<std::shared_ptr<Entity>>());
        entityLayer.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            map.at(i).push_back(nullptr);
            entityLayer.at(i).push_back(nullptr);
        }
    }
}

Area::~Area() {

}

sf::Vector2i Area::getDimensions() {
    return dimensions;
}

std::string &Area::getAreaName() {
    return areaName;
}

void Area::setMapTile(unsigned int x, unsigned int y, std::shared_ptr<Terrain> terrain) {
    map.at(x).at(y) = terrain;
}

void Area::setEntity(int x, int y, const std::shared_ptr<Entity> entity) {
    entityLayer.at((unsigned long) x).at((unsigned long) y) = entity;
}

void Area::spawnPlayer(int x, int y, unsigned int hp) {
    if(player == nullptr){
        player = std::shared_ptr<Player>(new Player(hp));
        movePlayer(x, y);
    }
    else{
        movePlayer(x, y);
    }
}

void Area::despawnPlayer() {
    setEntity(player->getWorldPosition().x, player->getWorldPosition().y, std::shared_ptr<Entity>(nullptr));
    player = nullptr;
}

Player Area::passPlayer() {
    return *player;
}

bool Area::moveEntity(int x, int y, const std::shared_ptr<Entity> &entity) {
    if((x >= 0 && x < dimensions.x) && (y >= 0 && y < dimensions.y)){
        if(getMapTile(x, y)->isPassable()){
            int prevXPos = entity->getWorldPosition().x;
            int prevYPos = entity->getWorldPosition().y;
            entity->setPrevPos(prevXPos, prevYPos);

            setEntity(prevXPos, prevYPos, std::shared_ptr<Entity>(nullptr));
            entity->setWorldPosition(x, y);
            setEntity(x, y, entity);

            return true;
        }
    }

    return false;
}

bool Area::movePlayer(int xOffset, int yOffset) {
    int xTarget = player->getWorldPosition().x + xOffset;
    int yTarget = player->getWorldPosition().y + yOffset;
    if(moveEntity(xTarget, yTarget, player)){
        GFX::gfx.centerCamera(player->getPreviousPosition(), player->getWorldPosition());
        return true;
    }

    return false;
}

bool Area::movePlayerToOtherArea(int xOffset, int yOffset, const std::shared_ptr<Area> &prevArea) {
    player = std::make_shared<Player>(prevArea->passPlayer());
    prevArea->despawnPlayer();
    player->setWorldPosition(0, 0);
    return movePlayer(xOffset, yOffset);
}

const std::shared_ptr<Terrain> & Area::getMapTile(int row, int col) {
    return map.at((unsigned long) row).at((unsigned long) col);
}

void Area::draw() {
    for(unsigned int i = 0; i < dimensions.x; i++){
        for(unsigned int j = 0; j < dimensions.y; j++){
            if(entityLayer.at(i).at(j) != nullptr){
                entityLayer.at(i).at(j)->render();
            }
            else if(map.at(i).at(j) != nullptr){
                map.at(i).at(j)->render();
            }
        }
    }
}

void Area::genRandom(const unsigned int &seed) {
    for(unsigned int i = 0; i < dimensions.x; i++){
        for(unsigned int j = 0; j < dimensions.y; j++){
            double x = (double)j / ((double) dimensions.y);
            double y = (double)i / ((double) dimensions.x);

            double n = PerlinNoise::NoiseWithSeed(seed, 10 * x, 10 * y, 0.8);

            if(n < 0.35){
                setMapTile(i, j, std::shared_ptr<Terrain>(new Water(i, j)));
            }
            else if(n >= 0.35 && n < 0.6){
                setMapTile(i, j, std::shared_ptr<Terrain>(new Grass(i, j)));
            }
            else if(n >= 0.6 && n < 0.8){
                setMapTile(i, j, std::shared_ptr<Terrain>(new Mountain(i, j)));
            }
            else{
                setMapTile(i, j, std::shared_ptr<Terrain>(new Snow(i, j)));
            }
        }
    }
}

void Area::setLocationalPosition(sf::Vector2i pos) {
    locationalPosition = pos;
}

sf::Vector2i Area::getLocationalPosition() {
    return locationalPosition;
}

void Area::resetRenderPos(int x, int y) {
    for(int i = 0; i < dimensions.x; i++){
        for(int j = 0; j < dimensions.y; j++){
            getMapTile(i, j)->setRenderPosition((i + x), (j + y));
        }
    }
}

const std::shared_ptr<Player> &Area::getPlayer() {
    return player;
}
