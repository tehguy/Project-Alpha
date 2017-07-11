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
#include <include/core/constants.hpp>
#include <include/enums/enums.hpp>

class Renderable {
public:
    Renderable(int x, int y, CORE::SYMBOL _symbol);

    void render();

    CORE::SYMBOL getSymbol();

    void setWorldPosition(int x, int y);

    unsigned int getWorldXPos();
    unsigned int getWorldYPos();

private:

    SDL_Rect mbox;

    unsigned int xpos, ypos;

    CORE::SYMBOL symbol;
};