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

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include <include/enums/enums.hpp>

class Terrain {
public:
    Terrain(int x, int y, std::string _symbol);

    std::string getSymbol() const;

    const std::string getTerrainSymbol();

    void render(SDL_Rect& camera);

    SDL_Rect& getBox();

    void setColor(Uint8 r, Uint8 g, Uint8 b);

private:
    int xpos, ypos;
    std::string symbol;

    SDL_Rect mbox;

    SDL_Color color;
};