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

#include "../gfx/renderable.hpp"

class Entity : public Renderable {
public:
    Entity(sf::Rect<int> spriteRect, unsigned int curhp, unsigned int maxhp);

    unsigned int getCurrentHP() const;
    unsigned int getMaxHP() const;

    virtual void addHP(unsigned int amtToAdd);
    virtual void removeHP(unsigned int amtToRem);

    void setPrevPos(int x, int y);
    sf::Vector2i getPreviousPosition() const;

    void setWorldPosition(int x, int y);
    sf::Vector2i getWorldPosition() const;

private:
    unsigned int curhp, maxhp;

    sf::Vector2i prevPosition, worldPosition;
};