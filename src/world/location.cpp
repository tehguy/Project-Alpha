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

#include "location.hpp"

Location::Location(std::string name, const int width, const int height) {
    locationName = std::move(name);

    dimensions = {width, height};

    initAreaVector();
}

void Location::initAreaVector() {
    for (unsigned int i = 0; i < dimensions.x; i++) {
        areas.emplace_back();
        areas.at(i).reserve(static_cast<unsigned long>(dimensions.y));

        for (unsigned int j = 0; j < dimensions.y; j++) {
            areas.at(i).emplace_back(nullptr);
        }
    }
}

sf::Vector2i Location::getLocationDimensions() const {
    return dimensions;
}

void Location::placeArea(int x, int y, Area area) {
    if (coordinatesWithinLocation(x, y)) {
        areas[x][y] = std::make_unique<Area>(area);
    }
}

bool Location::coordinatesWithinLocation(const int x, const int y) {
    return ((x >= 0) && (x < dimensions.x) && (y >= 0) && (y < dimensions.y));
}

std::string &Location::getLocationName() {
    return locationName;
}

void Location::setCurrentArea(unsigned int x, unsigned int y) {
    if (areas[x][y] != nullptr) {
        int cX = x, cY = y;

        center = {cX, cY};
    }
}

void Location::drawArea(const int x, const int y, const sf::Vector2i renderPos) {
    if (x < 0 || x >= dimensions.x) return;
    if (y < 0 || y >= dimensions.y) return;
    if (areas[x][y] == nullptr) return;

    areas[x][y]->resetRenderPos(renderPos.x, renderPos.y);
    areas[x][y]->drawArea();
}

void Location::drawChunk() {
    /* start drawing one space to the left/up, end before 2 spaces right/down */
    const int drawStartRelative = -1;
    const int drawEndRelative = 2;

    for (int x = drawStartRelative; x < drawEndRelative; x++) {
        int xOffset = x * CONSTANTS::GET_OBJECT().AREA_WIDTH;

        for (int y = drawStartRelative; y < drawEndRelative; y++) {
            int yOffset = y * CONSTANTS::GET_OBJECT().AREA_HEIGHT;
            drawArea((center.x + x), (center.y + y), {xOffset, yOffset});
        }
    }
}
