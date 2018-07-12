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

void Location::placeArea(const int x, const int y, const Area &area) {
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
        areas[x][y]->resetRenderPos(0, 0);

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
    int negXOffset = (-1) * CONSTANTS::GET_OBJECT().AREA_WIDTH;
    int negYOffset = (-1) * CONSTANTS::GET_OBJECT().AREA_HEIGHT;

    /* draw middle */
    drawArea(center.x, center.y, {0, 0});

    /* draw north area */
    drawArea(center.x, (center.y - 1), {0, negYOffset});

    /* draw north east area */
    drawArea((center.x + 1), (center.y - 1), {CONSTANTS::GET_OBJECT().AREA_WIDTH, negYOffset});

    /* draw east area */
    drawArea((center.x + 1), center.y, {CONSTANTS::GET_OBJECT().AREA_WIDTH, 0});

    /* draw south east area */
    drawArea((center.x + 1), (center.y + 1), {CONSTANTS::GET_OBJECT().AREA_WIDTH, CONSTANTS::GET_OBJECT().AREA_HEIGHT});

    /* draw south area */
    drawArea(center.x, (center.y + 1), {0, CONSTANTS::GET_OBJECT().AREA_HEIGHT});

    /* draw south west area */
    drawArea((center.x - 1), (center.y + 1), {negXOffset, CONSTANTS::GET_OBJECT().AREA_HEIGHT});

    /* draw west area */
    drawArea((center.x - 1), center.y, {negXOffset, 0});

    /* draw north west area */
    drawArea((center.x - 1), (center.y - 1), {negXOffset, negYOffset});
}
