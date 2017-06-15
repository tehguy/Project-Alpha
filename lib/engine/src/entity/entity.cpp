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

Entity::Entity(int chp, int mhp, std::vector<int> stats){
    currentHitPoints = chp;
    maxHitPoints = mhp;
    statArray = stats;
}

Entity::Entity(std::vector<int> stats) {
    statArray = stats;
}

int Entity::getCurrentHitPoints() {
    return currentHitPoints;
}

int Entity::getMaxHitPoints() {
    return maxHitPoints;
}

void Entity::setCurrentHitpoints(int hp) {
    currentHitPoints = hp;
}

void Entity::setMaxHitPoints(int hp) {
    maxHitPoints = hp;
}

int Entity::getAbs(STATS::ABS statToGet) {
    return statArray.at(statToGet);
}
