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

#pragma once

#include <google/protobuf/util/delimited_message_util.h>
#include <include/world/location.hpp>
#include <protos/world.pb.h>

#include <fstream>
#include <vector>

class WorldSaver {
public:
    WorldSaver();

    bool saveLocation(const std::shared_ptr<Location> &locationToSave);

private:
    bool openSaveFile(std::string fileName);
    void closeSaveFile();

    bool saveArea(const std::shared_ptr<Area> &areaToSave, world::Location_Area *areaSaver);
    bool saveTerrainObject(int xLoc, int yLoc, const std::shared_ptr<Terrain> &terrain,
                           world::Location_Area_Terrain *areaTerrainSaver);

    std::ofstream saveWriter;
};

namespace SAVE {
    extern WorldSaver worldSaver;
}