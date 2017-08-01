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

#pragma once

#include <include/core/io/fileio.hpp>
#include <vector>

class WorldSaver : public FileIO {
public:
    WorldSaver();

    bool saveLocation(const std::shared_ptr<Location> &locationToSave);

private:

    bool saveArea(const std::shared_ptr<Area> &areaToSave, WORLD::Area *areaSaver);
    bool saveTileObject(int xLoc, int yLoc, const std::shared_ptr<Tile> &tile, WORLD::Tile *tileSaver);
    bool saveTerrainObject(int xLoc, int yLoc, const std::shared_ptr<Terrain> &terrain,
                           WORLD::Terrain *areaTerrainSaver);

    std::ofstream saveWriter;
};