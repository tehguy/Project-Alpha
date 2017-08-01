/*
    Project Alpha
    Copyright (C) 2017  Pixima Development

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

Renderable::Renderable(unsigned int x, unsigned int y, sf::Rect<int> spriteRect) {

    worldSprite = GFX::gfx->createSprite(spriteRect);
    setRenderPosition(x, y);

    renderBox.width = CONSTANTS::TILE_WIDTH;
    renderBox.height = CONSTANTS::TILE_HEIGHT;
}

void Renderable::render() {
    if(GFX::gfx->checkWithinCamera(renderBox)){
        GFX::gfx->getWindow()->draw(worldSprite);
    }
}

void Renderable::setRenderPosition(int x, int y) {
    renderBox.left = x * CONSTANTS::TILE_WIDTH;
    renderBox.top = y * CONSTANTS::TILE_HEIGHT;

    worldSprite.setPosition(renderBox.left, renderBox.top);
}

