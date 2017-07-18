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

#include <include/world/location.hpp>

Location::Location(std::string name, int width, int height) {
    locationName = name;
    dimensions.x = width;
    dimensions.y = height;

    for(unsigned int i = 0; i < dimensions.x; i++){
        areas.push_back(std::vector<std::shared_ptr<Area>>());
        areas.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            areas.at(i).push_back(nullptr);
        }
    }
}

Location::~Location() {
    areas.clear();
}

sf::Vector2i Location::getDimensions() {
    return dimensions;
}

void Location::placeArea(unsigned int x, unsigned int y, Area area) {
    if((x >= 0) && (x < getDimensions().x) && (y >= 0) && (y < getDimensions().y)){
        area.setLocationalPosition(sf::Vector2i(x, y));
        areas.at(x).at(y) = std::make_shared<Area>(area);
    }
}

const std::shared_ptr<Area> Location::getArea(unsigned int x, unsigned int y) {
    return areas.at(x).at(y);
}

std::string &Location::getName() {
    return locationName;
}

void Location::setCurrentArea(int x, int y) {
    if(getArea((unsigned int) x, (unsigned int) y) != nullptr){
        currentArea = getArea((unsigned int) x, (unsigned int) y);
    }
}
const std::shared_ptr<Area> &Location::getCurrentArea() {
    return currentArea;
}

void Location::moveToArea(int xOffset, int yOffset) {
    int xTarget = currentArea->getLocationalPosition().x + xOffset;
    int yTarget = currentArea->getLocationalPosition().y + yOffset;

    if((xTarget >= 0) && (xTarget < getDimensions().x) && (yTarget >= 0) && (yTarget < getDimensions().y)){
        setCurrentArea(xTarget, yTarget);
    }
}
