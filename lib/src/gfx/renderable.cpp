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

#include <include/gfx/gfx.hpp>
#include <include/gfx/renderable.hpp>

Renderable::Renderable(unsigned int x, unsigned int y, CORE::SYMBOL _symbol) {
    mbox.left = x * CONSTANTS::TILE_WIDTH;
    mbox.top = y * CONSTANTS::TILE_HEIGHT;
    mbox.width = CONSTANTS::TILE_WIDTH;
    mbox.height = CONSTANTS::TILE_HEIGHT;

    symbol = _symbol;

    worldSprite = GFX::gfx.createSprite(_symbol);
    worldSprite.setPosition(mbox.left, mbox.top);
}

void Renderable::render() {
    GFX::gfx.getWindow()->draw(worldSprite);
}

CORE::SYMBOL Renderable::getSymbol() {
    return symbol;
}

void Renderable::setWorldPosition(unsigned int x, unsigned int y) {
    mbox.left = x * CONSTANTS::TILE_WIDTH;
    mbox.top = y * CONSTANTS::TILE_HEIGHT;

    worldSprite.setPosition(sf::Vector2f(mbox.left, mbox.top));
}

unsigned int Renderable::getWorldXPos() {
    return (unsigned int) mbox.left;
}

unsigned int Renderable::getWorldYPos() {
    return (unsigned int) mbox.top;
}
