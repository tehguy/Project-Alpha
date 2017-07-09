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

#include <include/core/core.hpp>

Terrain::Terrain(int x, int y, CORE::SYMBOL _symbol) {
    symbol = _symbol;
    mbox.x = x;
    mbox.y = y;
    mbox.w = TILE_WIDTH;
    mbox.h = TILE_HEIGHT;
}

CORE::SYMBOL Terrain::getSymbol() const {
    return symbol;
}

void Terrain::render(SDL_Rect &camera) {
    if(MAIN::core.checkCollision(camera, mbox)){
        MAIN::core.getTileTexture().render((mbox.x - camera.x)*TILE_WIDTH, (mbox.y - camera.y)*TILE_HEIGHT,
                                           &MAIN::core.getTileTexture().getClip(symbol));
    }
}

SDL_Rect &Terrain::getBox() {
    return mbox;
}