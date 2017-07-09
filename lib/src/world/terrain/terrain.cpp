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

Terrain::Terrain(int x, int y, std::string _symbol) {
    symbol = _symbol;
    mbox.x = x + 1;
    mbox.y = y + 1;
}

std::string Terrain::getSymbol() const {
    return symbol;
}

const std::string Terrain::getTerrainSymbol() {
    return symbol;
}

void Terrain::render(SDL_Rect &camera) {
    MAIN::core.getTileTexture().loadFromRenderedText(symbol, color);

    if(MAIN::core.checkCollision(camera, mbox)){
        MAIN::core.getTileTexture().render((mbox.x - camera.x)*MAIN::TEXT_SIZE, (mbox.y - camera.y)*MAIN::TEXT_SIZE);
    }
}

SDL_Rect &Terrain::getBox() {
    return mbox;
}

void Terrain::setColor(Uint8 r, Uint8 g, Uint8 b) {
    color = {r, g, b};
}
