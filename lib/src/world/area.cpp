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

    for(unsigned int i = 0; i < dimensions.x; i++){
        map.push_back(std::vector<Terrain*>());
        map.at(i).reserve((unsigned long) dimensions.y);

        specialMap.push_back(std::vector<SpecialTile*>());
        specialMap.at(i).reserve((unsigned long) dimensions.y);

        entityLayer.push_back(std::vector<Entity*>());
        entityLayer.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            map.at(i).push_back(nullptr);
            specialMap.at(i).push_back(nullptr);
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

void Area::setMapSymbol(unsigned int x, unsigned int y, Terrain *terrain) {
    map.at(x).at(y) = terrain;
}

void Area::setItemSymbol(unsigned int x, unsigned int y, Item *item) {
    itemLayer.at(x).at(y) = item;
}

void Area::setEntitySymbol(unsigned int x, unsigned int y, Entity *entity) {
    entityLayer.at(x).at(y) = entity;
}

bool Area::moveEntity(int x, int y, Entity &entity) {
    if((x >= 0 && x < dimensions.x) && (y >= 0 && y < dimensions.y)){
        CORE::SYMBOL target = getMapSymbol((unsigned int) x, (unsigned int) y);

        if(target != CORE::SYMBOL::WATER && target != CORE::SYMBOL::MOUNTAIN){
            int prevXPos = entity.getWorldPosition().x;
            int prevYPos = entity.getWorldPosition().y;
            entity.setPrevPos(prevXPos, prevYPos);

            if(getEntitySymbol((unsigned int) prevXPos, (unsigned int) prevYPos) == entity.getSymbol()){
                setEntitySymbol((unsigned int) prevXPos, (unsigned int) prevYPos, nullptr);
            }

            entity.setWorldPosition((unsigned int) x, (unsigned int) y);
            setEntitySymbol((unsigned int) x, (unsigned int) y, &entity);

            return true;
        }
    }

    return false;
}

bool Area::movePlayer(int xOffset, int yOffset, Entity &player) {
    return moveEntity((player.getWorldPosition().x + xOffset), (player.getWorldPosition().y + yOffset), player);
}

const CORE::SYMBOL Area::getMapSymbol(unsigned int row, unsigned int col) {
    if(map.at(row).at(col) != nullptr){
        return map.at(row).at(col)->getSymbol();
    }

    return CORE::SYMBOL::NOSYM;
}

const CORE::SYMBOL Area::getItemSymbol(unsigned int x, unsigned int y) {
    if(itemLayer.at(x).at(y) != nullptr){
        return itemLayer.at(x).at(y)->getSymbol();
    }

    return CORE::SYMBOL::NOSYM;
}

const CORE::SYMBOL Area::getEntitySymbol(unsigned int row, unsigned int col) {
    if(entityLayer.at(row).at(col) != nullptr){
        return entityLayer.at(row).at(col)->getSymbol();
    }

    return CORE::SYMBOL::NOSYM;
}

void Area::draw() {
    for(unsigned int i = 0; i < dimensions.x; i++){
        for(unsigned int j = 0; j < dimensions.y; j++){
            if(entityLayer.at(i).at(j)){
                entityLayer.at(i).at(j)->render();
            }
            else if(map.at(i).at(j)){
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
                setMapSymbol(i, j, new Water(i, j));
            }
            else if(n >= 0.35 && n < 0.6){
                setMapSymbol(i, j, new Grass(i, j));
            }
            else if(n >= 0.6 && n < 0.8){
                setMapSymbol(i, j, new Mountain(i, j));
            }
            else{
                setMapSymbol(i, j, new Snow(i, j));
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
