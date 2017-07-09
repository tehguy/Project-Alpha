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

#include <include/core/core.hpp>
#include <include/core/randomnumbergenerator.hpp>

#include <include/world/terrain/grass.hpp>
#include <include/world/terrain/snow.hpp>
#include <include/world/terrain/wall.hpp>
#include <include/world/terrain/water.hpp>

Area::Area(std::string id, unsigned int _width, unsigned int _height) {
    identifier = id;
    width = _width;
    height = _height;

    areaNorth = nullptr;
    areaEast = nullptr;
    areaSouth = nullptr;
    areaWest = nullptr;

    for(unsigned int i = 0; i < height; i++){
        map.push_back(std::vector<Terrain>());
        map.at(i).reserve(width);

        for(unsigned int j = 0; j < width; j++){
            map.at(i).push_back(Terrain(i, j, " "));
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

void Area::setMapSymbol(unsigned int row, unsigned int col, Terrain terrain) {
    map.at(row).at(col) = terrain;
}

void Area::setItemSymbol(unsigned int row, unsigned int col, char symbol) {
    itemLayer.at(row).at(col) = symbol;
}

void Area::setEntitySymbol(unsigned int row, unsigned int col, char symbol) {
    entityLayer.at(row).at(col) = symbol;
}

const std::string Area::getMapSymbol(unsigned int row, unsigned int col) {
    return map.at(row).at(col).getTerrainSymbol();
}

const Terrain Area::getMapTerrain(unsigned int row, unsigned int col) {
    return map.at(row).at(col);
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
    for(auto& innerVec : map){
        for(auto& terrain : innerVec){
            terrain.render(MAIN::core.getCamrea());
        }
    }
}

void Area::genRandom() {
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            int num = RandomNumberGenerator::RollDice(0, 3);

            switch (num){
                case 0:
                    map.at(i).at(j) = Grass(i, j);
                    break;
                case 1:
                    map.at(i).at(j) = Snow(i, j);
                    break;
                case 2:
                    map.at(i).at(j) = Wall(i, j);
                    break;
                case 3:
                    map.at(i).at(j) = Water(i, j);
                    break;
                default:
                    map.at(i).at(j) = Water(i, j);
                    break;
            }
        }
    }
}
