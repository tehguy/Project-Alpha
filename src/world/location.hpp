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

#pragma once

#include <string>
#include <SFML/System.hpp>

#include "area.hpp"

class Location {
public:
    Location(std::string name, int width, int height);

    sf::Vector2i getLocationDimensions() const;

    void placeArea(int x, int y, const Area &area);

    std::string & getLocationName();

    void setCurrentArea(unsigned int x, unsigned int y);

    void drawChunk();

private:
    bool coordinatesWithinLocation(int x, int y);

    void initAreaVector();

    void drawArea(int x, int y, sf::Vector2i renderPos);

    typedef std::vector<std::vector<std::unique_ptr<Area>>> areaVec;

    areaVec areas;

    sf::Vector2i dimensions;
    sf::Vector2i center;

    std::string locationName;
};