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

#include <include/core/worldsaver.hpp>
#include <iostream>

namespace SAVE {
    WorldSaver worldSaver;
}

WorldSaver::WorldSaver() {

}

bool WorldSaver::openSaveFile(std::string fileName) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::cout << fileName << std::endl;
    saveWriter.open(fileName, std::ios::out | std::ios::app);
    return saveWriter.is_open();
}

void WorldSaver::closeSaveFile() {
    saveWriter.close();
    google::protobuf::ShutdownProtobufLibrary();
}

bool WorldSaver::saveLocation(Location &locationToSave) {
    bool result = false;

    if(openSaveFile(locationToSave.genFileName())){
        world::Location locationSaver;

        locationSaver.set_name(locationToSave.getName());
        locationSaver.set_width(locationToSave.getDimensions().x);
        locationSaver.set_height(locationToSave.getDimensions().y);

        result = saveArea(locationToSave, &locationSaver);
    }

    closeSaveFile();

    return result;
}

bool WorldSaver::saveArea(Location &locationToSave, world::Location *areaSaver) {


    return false;
}

bool WorldSaver::saveTerrainObjects(std::vector<std::vector<std::shared_ptr<Terrain>>> &terrainMap,
                                    world::Location_Area_Terrain *areaTerrainSaver) {


    //bool result = google::protobuf::util::SerializeDelimitedToOstream(terrainLayer, &saveWriter);
    closeSaveFile();

    return false;
}
