/*
    Project Alpha
    Copyright (C) 2017  Pixima Development

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

#include <include/mapgen/mworld/marea.hpp>
#include <include/world/location.hpp>

class MLocation {
public:
    MLocation(std::string name, int width, int height);

    sf::Vector2i getDimensions();

    void createArea();
    void placeArea(int x, int y, MArea area);
    const std::shared_ptr<MArea> & getArea(int x, int y);

    std::string getName();

    void setCurrentArea(int x, int y);
    const std::shared_ptr<MArea>& getCurrentMArea();

    void drawChunk();

    void moveCursor(int xOffset, int yOffset);

    std::shared_ptr<Location>& getHeldLocation();

private:

    void moveToMArea(int xOffset, int yOffset);

    void loadAdjacentMAreas();

    std::vector<std::vector<std::shared_ptr<MArea>>> chunk;

    std::vector<std::vector<std::shared_ptr<MArea>>> areas;

    sf::Vector2i dimensions;

    std::string locationName;

    std::shared_ptr<Location> heldLocation;
};