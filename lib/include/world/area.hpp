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

#include <string>
#include <vector>

class Area {
public:
    Area(std::string id, unsigned int _width, unsigned int _height);

    const std::string& getIdentifier();

    unsigned int getWidth();
    unsigned int getHeight();

    void setMapSymbol(unsigned int row, unsigned int col, char symbol);
    void setItemSymbol(unsigned int row, unsigned int col, char symbol);
    void setEntitySymbol(unsigned int row, unsigned int col, char symbol);

    const char getMapSymbol(unsigned int row, unsigned int col);

private:
    void genBlankMap();

    std::string identifier;

    unsigned int width, height;

    std::vector<std::vector<char>> map;
    std::vector<std::vector<char>> itemLayer;
    std::vector<std::vector<char>> entityLayer;
};