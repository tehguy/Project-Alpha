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

Player::Player(int row_0, int col_0, unsigned int maxhp) : Entity(CORE::SYMBOL::PLAYER, CORE::CSYMBOL::CPLAYER,
                                                                  maxhp, maxhp) {
    row = row_0;
    col = col_0;
}

void Player::pos(int row_0, int col_0) {
    row = row_0;
    col = col_0;
}

int Player::getRow() {
    return row;
}

int Player::getCol() {
    return col;
}