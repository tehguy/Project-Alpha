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

#include <include/entity/entity.hpp>

Entity::Entity(char _symbol, unsigned int _curhp, unsigned int _maxhp) {
    symbol = _symbol;
    curhp = _curhp;
    maxhp = _maxhp;
}

const unsigned int Entity::getSymbol() {
    return (const unsigned int) symbol;
}

const unsigned int Entity::getCurHP() {
    return curhp;
}

const unsigned int Entity::getMaxHP() {
    return maxhp;
}

void Entity::addHP(unsigned int amtToAdd) {
    curhp += amtToAdd;
    if(curhp > maxhp) {
        curhp = maxhp;
    }
}

void Entity::remHP(unsigned int amtToRem) {
    curhp -= amtToRem;
    if(curhp < 0) {
        curhp = 0;
    }
}
