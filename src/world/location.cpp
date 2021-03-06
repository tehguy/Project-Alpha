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
        int cenX = x, cenY = y;

        currentAreaCoords = {cenX, cenY};
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
            drawArea((currentAreaCoords.x + x), (currentAreaCoords.y + y), {xOffset, yOffset});
        }
    }
}

bool Location::canMoveToPosition(sf::Vector2i moveTo) {
    auto curX = static_cast<unsigned int>(currentAreaCoords.x), curY = static_cast<unsigned int>(currentAreaCoords.y);

    bool canPass;

    if (moveTo.x >= areas[curX][curY]->getAreaDimensions().x) {
        if ((curX + 1) >= dimensions.x) return false;
        if (areas[curX + 1][curY] == nullptr) return false;

        int adjustedMoveX = moveTo.x - areas[curX][curY]->getAreaDimensions().x;
        canPass = areas[curX + 1][curY]->collisionExistsAtPoint(static_cast<unsigned int>(adjustedMoveX),
                                                             static_cast<unsigned int>(moveTo.y));

    } else if (moveTo.x < 0) {
        if ((curX - 1) < 0) return false;
        if (areas[curX - 1][curY] == nullptr) return false;

        int adjustedMoveX = moveTo.x + areas[curX][curY]->getAreaDimensions().x;
        canPass = areas[curX - 1][curY]->collisionExistsAtPoint(static_cast<unsigned int>(adjustedMoveX),
                                                             static_cast<unsigned int>(moveTo.y));

    } else if (moveTo.y >= areas[curX][curY]->getAreaDimensions().y) {
        if ((curY + 1) >= dimensions.y) return false;
        if (areas[curX][curY + 1] == nullptr) return false;

        int adjustedMoveY = moveTo.y - areas[curX][curY]->getAreaDimensions().y;
        canPass = areas[curX][curY + 1]->collisionExistsAtPoint(static_cast<unsigned int>(moveTo.x),
                                                             static_cast<unsigned int>(adjustedMoveY));

    } else if (moveTo.y < 0) {
        if ((curY - 1) < 0) return false;
        if (areas[curX][curY - 1] == nullptr) return false;

        int adjustedMoveY = moveTo.y + areas[curX][curY]->getAreaDimensions().y;
        canPass = areas[curX][curY - 1]->collisionExistsAtPoint(static_cast<unsigned int>(moveTo.x),
                                                             static_cast<unsigned int>(adjustedMoveY));

    } else {
        canPass = areas[curX][curY]->collisionExistsAtPoint(static_cast<unsigned int>(moveTo.x),
                                                            static_cast<unsigned int>(moveTo.y));

    }

    return canPass;
}