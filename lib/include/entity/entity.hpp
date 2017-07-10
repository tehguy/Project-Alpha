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

#include <include/core/constants.hpp>
#include <include/enums/enums.hpp>
#include <include/gfx/renderable.hpp>
#include <SDL2/SDL.h>

class Entity : public Renderable {
public:
    Entity(CORE::SYMBOL _symbol, int x, int y, unsigned int _curhp, unsigned int _maxhp);

    const unsigned int getCurHP();
    const unsigned int getMaxHP();

    virtual void addHP(unsigned int amtToAdd);
    virtual void remHP(unsigned int amtToRem);

    void setPos(unsigned int _xpos, unsigned int _ypos);
    unsigned int getWorldXPos();
    unsigned int getWorldYPos();

private:

    unsigned int curhp, maxhp;

    unsigned int xpos, ypos, size;
};