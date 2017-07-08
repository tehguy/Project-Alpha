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

#include <include/entity/player.hpp>

Player::Player(unsigned int row_0, unsigned int col_0, unsigned int maxhp) : Entity(CORE::SYMBOL::PLAYER,
                                                                                    maxhp, maxhp) {
    row = row_0;
    col = col_0;
    curExp = 0;
    expToNextLevel = 100;
}

void Player::pos(unsigned int row_0, unsigned int col_0) {
    row = row_0;
    col = col_0;
}

unsigned int Player::getRow() {
    return row;
}

unsigned int Player::getCol() {
    return col;
}

unsigned int Player::getCurExp() {
    return curExp;
}

unsigned int Player::getExpToNextLevel() {
    return expToNextLevel;
}

void Player::addExpPoints(unsigned int amtToAdd) {
    curExp += amtToAdd;
    if(curExp > expToNextLevel){
        curExp = expToNextLevel;
    }
}

void Player::remExpPoints(unsigned int amtToRem) {
    curExp -= amtToRem;
    if(curExp < 0){
        curExp = 0;
    }
}

void Player::addHP(unsigned int amtToAdd) {
    Entity::addHP(amtToAdd);
}

void Player::remHP(unsigned int amtToRem) {
    Entity::remHP(amtToRem);
}
