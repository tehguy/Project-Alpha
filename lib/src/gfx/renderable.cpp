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

#include <include/gfx/renderable.hpp>
#include <include/gfx/gfx.hpp>

Renderable::Renderable(int x, int y, CORE::SYMBOL _symbol) {
    mbox.x = x;
    mbox.y = y;
    mbox.w = CONSTANTS::TILE_WIDTH;
    mbox.h = CONSTANTS::TILE_HEIGHT;

    symbol = _symbol;
}

void Renderable::render() {
    if(GFX::checkCollision(GFX::camera, mbox)){
        GFX::gTileTexture.render((mbox.x - GFX::camera.x)*mbox.w, (mbox.y - GFX::camera.y)*mbox.h,
                                           &GFX::gTileTexture.getClip(symbol));
    }
}

CORE::SYMBOL Renderable::getSymbol() {
    return symbol;
}

void Renderable::setMboxPos(int x, int y) {
    mbox.x = x;
    mbox.y = y;
}
