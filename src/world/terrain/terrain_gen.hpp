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

#pragma once

#include "../tile.hpp"

namespace TERRAIN_GEN {
    Tile GEN_SPACE_VERT(const unsigned int x, const unsigned int y) {
        Terrain space(Terrain::TYPE::NONE, false);

        return Tile(x, y, space);
    }

    Tile GEN_GRASS_VERT(const unsigned int x, const unsigned int y) {
        Terrain grass(Terrain::TYPE::GRASS, true);
        Tile tile(x, y, grass);
        return tile;
    }

    Tile GEN_WATER_VERT(const unsigned int x, const unsigned int y) {
        Terrain water(Terrain::TYPE::WATER, true);

        return Tile(x, y, water);
    }

    Tile GEN_MOUNTAIN_VERT(const unsigned int x, const unsigned int y) {
        Terrain mountain(Terrain::TYPE::MOUNTAIN, false);

        return Tile(x, y, mountain);
    }

    Tile GEN_SNOW_VERT(const unsigned int x, const unsigned int y) {
        Terrain snow(Terrain::TYPE::SNOW, true);

        return Tile(x, y, snow);
    }
}