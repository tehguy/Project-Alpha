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
    Tile GEN_SPACE(const int x, const int y) {
        Terrain space(CONSTANTS::GET_OBJECT().BLANK_SPRITE_RECT, Terrain::TYPE::NONE, false);

        return Tile(x, y, space);
    }

    Tile GEN_GRASS(const int x, const int y) {
        Terrain grass(CONSTANTS::GET_OBJECT().GRASS_SPRITE_RECT, Terrain::TYPE::GRASS, true);

        return Tile(x, y, grass);
    };

    Tile GEN_WATER(const int x, const int y) {
        Terrain water(CONSTANTS::GET_OBJECT().WATER_SPRITE_RECT, Terrain::TYPE::WATER, true);

        return Tile(x, y, water);
    };

    Tile GEN_MOUNTAIN(const int x, const int y) {
        Terrain mountain(CONSTANTS::GET_OBJECT().MOUNTAIN_SPRITE_RECT, Terrain::TYPE::MOUNTAIN, false);;

        return Tile(x, y, mountain);
    }

    Tile GEN_SNOW(const int x, const int y) {
        Terrain snow(CONSTANTS::GET_OBJECT().SNOW_SPRITE_RECT, Terrain::TYPE::SNOW, true);

        return Tile(x, y, snow);
    }
}