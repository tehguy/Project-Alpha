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

#include "renderable.hpp"
#include "gfx.hpp"

Renderable::Renderable(unsigned int x, unsigned int y, sf::Rect<int> spriteRect) {
    worldSprite = Graphics::Instance().createSprite(spriteRect);
    setRenderPosition(x, y);

    renderBox.width = CONSTANTS::GET_OBJECT().TILE_WIDTH;
    renderBox.height = CONSTANTS::GET_OBJECT().TILE_HEIGHT;
}

Renderable::Renderable(unsigned int x, unsigned int y, int tileID) {
    generateQuadCoords(x, y);
    generateTexCoords(tileID);
}

void Renderable::render() {
    Graphics::Instance().draw(worldSprite, renderBox);
}

void Renderable::queueRender() const {
    Graphics::Instance().addTileToDrawBatch(quad);
}


void Renderable::setRenderPosition(const int x, const int y) {
    renderBox.left = x * CONSTANTS::GET_OBJECT().TILE_WIDTH;
    renderBox.top = y * CONSTANTS::GET_OBJECT().TILE_HEIGHT;

    worldSprite.setPosition(renderBox.left, renderBox.top);

    generateQuadCoords(x, y);
}

void Renderable::generateQuadCoords(const unsigned int x, const unsigned int y) {
    int width = CONSTANTS::GET_OBJECT().TILE_WIDTH;
    int height = CONSTANTS::GET_OBJECT().TILE_HEIGHT;

    if (!quad.empty()) {
        quad.clear();
        quad.reserve(4);
    }

    quad.emplace_back(sf::Vector2f(x * width, y * height));
    quad.emplace_back(sf::Vector2f((x + 1) * width, y * height));
    quad.emplace_back(sf::Vector2f((x + 1) * width, (y + 1) * height));
    quad.emplace_back(sf::Vector2f(x * width, (y + 1) * height));
}

void Renderable::generateTexCoords(int tileID) {
    sf::Vector2u texSize = Graphics::Instance().getTextureSize();
    sf::Vector2i tileSize(CONSTANTS::GET_OBJECT().TILE_WIDTH, CONSTANTS::GET_OBJECT().TILE_HEIGHT);

    int tu = tileID % (texSize.x / tileSize.x);
    int tv = tileID / (texSize.x / tileSize.x);

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
}
