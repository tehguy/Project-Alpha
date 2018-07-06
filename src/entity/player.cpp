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

#include "player.hpp"

Player::Player(unsigned int maxhp) : Entity(CONSTANTS::GET_OBJECT().PLAYER_SPRITE_RECT, maxhp, maxhp), curExp(0),
                                     expToNextLevel(100) {}

unsigned int Player::getCurExp() const {
    return curExp;
}

unsigned int Player::getExpToNextLevel() const {
    return expToNextLevel;
}

void Player::addExpPoints(unsigned int amtToAdd) {
    curExp += amtToAdd;
    if (curExp > expToNextLevel) {
        curExp = expToNextLevel;
    }
}

void Player::remExpPoints(unsigned int amtToRem) {
    curExp -= amtToRem;
    if (curExp < 0) {
        curExp = 0;
    }
}

void Player::removeHP(unsigned int amtToRem) {
    Entity::removeHP(amtToRem);
}

void Player::addHP(unsigned int amtToAdd) {
    Entity::addHP(amtToAdd);
}