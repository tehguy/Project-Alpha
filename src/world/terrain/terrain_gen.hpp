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

#include "terrain.hpp"

namespace TERRAIN_GEN {
    Terrain GEN_SPACE(const int x, const int y) {
        return Terrain(x, y, CONSTANTS::GET_OBJECT().BLANK_SPRITE_RECT, Terrain::TYPE::NONE, false);
    }

    Terrain GEN_GRASS(const int x, const int y) {
        return Terrain(x, y, CONSTANTS::GET_OBJECT().GRASS_SPRITE_RECT, Terrain::TYPE::GRASS);
    };

    Terrain GEN_WATER(const int x, const int y) {
        return Terrain(x, y, CONSTANTS::GET_OBJECT().WATER_SPRITE_RECT, Terrain::TYPE::WATER);
    };

    Terrain GEN_MOUNTAIN(const int x, const int y) {
        return Terrain(x, y, CONSTANTS::GET_OBJECT().MOUNTAIN_SPRITE_RECT, Terrain::TYPE::MOUNTAIN, false);
    }

    Terrain GEN_SNOW(const int x, const int y) {
        return Terrain(x, y, CONSTANTS::GET_OBJECT().SNOW_SPRITE_RECT, Terrain::TYPE::SNOW);
    }
}