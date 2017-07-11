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

Area::Area(std::string id, unsigned int _width, unsigned int _height) {
    identifier = id;
    width = _width;
    height = _height;

    areaNorth = nullptr;
    areaEast = nullptr;
    areaSouth = nullptr;
    areaWest = nullptr;

    for(unsigned int i = 0; i < width; i++){
        map.push_back(std::vector<Terrain*>());
        map.at(i).reserve(height);

        entityLayer.push_back(std::vector<Entity*>());
        entityLayer.at(i).reserve(height);

        for(unsigned int j = 0; j < height; j++){
            map.at(i).push_back(nullptr);
            entityLayer.at(i).push_back(nullptr);
        }
    }
}

Area::~Area() {

}

const std::string &Area::getIdentifier() {
    return identifier;
}

unsigned int Area::getWidth() {
    return width;
}

unsigned int Area::getHeight() {
    return height;
}

void Area::setMapSymbol(unsigned int x, unsigned int y, Terrain *terrain) {
    map.at(x).at(y) = terrain;
}

void Area::setItemSymbol(unsigned int x, unsigned int y, char symbol) {
    itemLayer.at(x).at(y) = symbol;
}

void Area::setEntitySymbol(unsigned int x, unsigned int y, Entity *entity) {
    entityLayer.at(x).at(y) = entity;
}

bool Area::moveEntity(unsigned int x, unsigned int y, Entity &entity) {
    if((x >= 0 && x < width) && (y >= 0 && y < height)){
        CORE::SYMBOL target = getMapSymbol(x, y);

        if(target != CORE::SYMBOL::WATER && target != CORE::SYMBOL::MOUNTAIN){
            unsigned int prevXPos = entity.getWorldXPos();
            unsigned int prevYPos = entity.getWorldYPos();
            entity.setPrevPos(prevXPos, prevYPos);

            if(getEntitySymbol(prevXPos, prevYPos) == entity.getSymbol()){
                setEntitySymbol(prevXPos, prevYPos, nullptr);
            }

            entity.setWorldPosition(x, y);
            setEntitySymbol(x, y, &entity);

            return true;
        }
    }

    return false;
}

const CORE::SYMBOL Area::getMapSymbol(unsigned int row, unsigned int col) {
    return map.at(row).at(col)->getSymbol();
}

const CORE::SYMBOL Area::getEntitySymbol(unsigned int row, unsigned int col) {
    if(entityLayer.at(row).at(col) != nullptr){
        return entityLayer.at(row).at(col)->getSymbol();
    }

    return CORE::SYMBOL::NOSYM;
}

void Area::unlinkAreas() {
    areaNorth = nullptr;
    areaEast = nullptr;
    areaSouth = nullptr;
    areaWest = nullptr;
}

void Area::setAreaNorth(Area &area) {
    *areaNorth = area;
}

void Area::setAreaEast(Area &area) {
    *areaEast = area;
}

void Area::setAreaSouth(Area &area) {
    *areaSouth = area;
}

void Area::setAreaWest(Area &area) {
    *areaWest = area;
}

std::shared_ptr<Area> &Area::getAreaNorth() {
    return areaNorth;
}

std::shared_ptr<Area> &Area::getAreaEast() {
    return areaEast;
}

std::shared_ptr<Area> &Area::getAreaSouth() {
    return areaSouth;
}

std::shared_ptr<Area> &Area::getAreaWest() {
    return areaWest;
}

void Area::draw() {
    for(unsigned int i = 0; i < width; i++){
        for(unsigned int j = 0; j < height; j++){
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
    for(unsigned int i = 0; i < width; i++){
        for(unsigned int j = 0; j < height; j++){
            double x = (double)j / ((double) height);
            double y = (double)i / ((double) width);

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
