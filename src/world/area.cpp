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

#include "area.hpp"

#include "../core/perlin_noise.hpp"
#include "terrain/terrain_gen.hpp"

Area::Area(std::string name) {
    areaName = std::move(name);

    areaDimensions = {CONSTANTS::GET_OBJECT().AREA_WIDTH, CONSTANTS::GET_OBJECT().AREA_HEIGHT};

    tileMap.reserve(static_cast<unsigned long>(areaDimensions.x));

    for (unsigned int i = 0; i < areaDimensions.x; i++) {
        tileMap.emplace_back();
        tileMap.at(i).reserve(static_cast<unsigned long>(areaDimensions.y));

        for (unsigned int j = 0; j < areaDimensions.y; j++) {
            tileMap.at(i).emplace_back(TERRAIN_GEN::GEN_SPACE(i, j));
        }
    }
}


sf::Vector2i Area::getAreaDimensions() const {
    return areaDimensions;
}

std::string &Area::getAreaName() {
    return areaName;
}

void Area::drawArea() {
    for (auto& innerVec : tileMap) {
        for (auto& tile : innerVec) {
            tile.draw();
        }
    }
}

void Area::setMapTile(const unsigned int x, const unsigned int y, const Tile &tile) {
    tileMap.at(x).at(y) = tile;
}

Tile &Area::getMapTile(const unsigned int x, const unsigned int y) {
    return tileMap.at(x).at(y);
}

void Area::genRandom(const unsigned int seed) {
    for (unsigned int i = 0; i < areaDimensions.x; i++) {
        for (unsigned int j = 0; j < areaDimensions.y; j++) {
            float x = ((float) j) / ((float) areaDimensions.y);
            float y = ((float) i) / ((float) areaDimensions.x);

            float n = PerlinNoise::Instance().GenNoiseWithSeed(seed, 10 * x, 10 * y, 0.8);

            if (n < 0.35f) {
                setMapTile(i, j, TERRAIN_GEN::GEN_WATER(i, j));
            }
            else if (n >= 0.35f && n < 0.6f) {
                setMapTile(i, j, TERRAIN_GEN::GEN_GRASS(i, j));
            }
            else if (n >= 0.6f && n < 0.8f) {
                setMapTile(i, j, TERRAIN_GEN::GEN_MOUNTAIN(i, j));
            }
            else {
                setMapTile(i, j, TERRAIN_GEN::GEN_SNOW(i, j));
            }
        }
    }
}

bool Area::collisionExistsAtPoint(const unsigned int x, const unsigned int y) {
    return tileMap.at(x).at(y).isPassable();
}

void Area::resetRenderPos(const int x, const int y) {
    for (int i = 0; i < areaDimensions.x; i++) {
        for (int j = 0; j < areaDimensions.y; j++) {
            int xTarget = i + x;
            int yTarget = j + y;

            getMapTile(static_cast<unsigned int>(xTarget), static_cast<unsigned int>(yTarget))
                    .resetRenderPosition(xTarget, yTarget);
        }
    }
}

