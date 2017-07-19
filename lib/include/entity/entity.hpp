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

class Entity : public Renderable {
public:
    Entity(CORE::SYMBOL _symbol, unsigned int _curhp, unsigned int _maxhp);

    const unsigned int getCurHP();
    const unsigned int getMaxHP();

    virtual void addHP(unsigned int amtToAdd);
    virtual void remHP(unsigned int amtToRem);

    void setPrevPos(int x, int y);
    sf::Vector2i getPreviousPosition();

    void setWorldPosition(int x, int y);

    sf::Vector2i getWorldPosition();

private:
    unsigned int curhp, maxhp;

    sf::Vector2i prevPosition;
    sf::Vector2i worldPosition;
};