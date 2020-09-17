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

#include <mpif-sizeof.h>
#include "terrain.hpp"

Terrain::Terrain(const sf::Rect<int> &spriteRect, TYPE type, bool isPassable) : Renderable(0, 0, spriteRect),
                                                                                passable(isPassable), ttype(type) {}

Terrain::Terrain(TYPE type, bool isPassable) : Renderable(0, 0, type), passable(isPassable),
                                               ttype(type) {}

bool Terrain::isPassable() const {
    return passable;
}

int Terrain::getType() const {
    return ttype;
}
