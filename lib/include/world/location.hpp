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

#pragma once

#include <include/world/area.hpp>

#include <memory>

class Location {
public:
    Location(std::string name, int width, int height);
    ~Location();

    sf::Vector2i getDimensions();

    void placeArea(unsigned int x, unsigned int y, Area area);

    const std::shared_ptr<Area> & getArea(int x, int y);

    std::string getName();

    void setCurrentArea(int x, int y);
    const std::shared_ptr<Area>& getCurrentArea();
    void moveToArea(int xOffset, int yOffset);

    void loadAdjacentAreas();
    void drawChunk();

    void movePlayer(int xOffset, int yOffset);

    std::string genFileName();

private:

    std::shared_ptr<Area> currentArea;
    std::shared_ptr<Area> nArea;
    std::shared_ptr<Area> eArea;
    std::shared_ptr<Area> sArea;
    std::shared_ptr<Area> wArea;

    std::shared_ptr<Area> neArea;
    std::shared_ptr<Area> seArea;
    std::shared_ptr<Area> swArea;
    std::shared_ptr<Area> nwArea;

    std::vector<std::vector<std::shared_ptr<Area>>> areas;

    sf::Vector2i dimensions;

    std::string locationName;
};