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
    saveWriter.open(fileName);
    return saveWriter.is_open();
}

void WorldSaver::closeSaveFile() {
    saveWriter.close();
    google::protobuf::ShutdownProtobufLibrary();
}

bool WorldSaver::saveLocation(const std::shared_ptr<Location> &locationToSave) {
    bool result = false;

    std::string locName = locationToSave->getName();
    std::string saveFileName = "./save/" + locName + ".map";

    if(openSaveFile(saveFileName)){
        world::Location locationSaver;

        int width = locationToSave->getDimensions().x;
        int height = locationToSave->getDimensions().y;

        locationSaver.set_name(locName);
        locationSaver.set_width(width);
        locationSaver.set_height(height);

        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                result = saveArea(locationToSave->getArea(i, j), locationSaver.add_areas());

                if(!result){
                    return false;
                }
            }
        }

        result = google::protobuf::util::SerializeDelimitedToOstream(locationSaver, &saveWriter);
    }

    closeSaveFile();

    return result;
}

bool WorldSaver::saveArea(const std::shared_ptr<Area> &areaToSave, world::Location_Area *areaSaver) {
    areaSaver->set_name(areaToSave->getAreaName());

    bool result;

    for(int i = 0; i < areaToSave->getDimensions().x; i++){
        for(int j = 0; j < areaToSave->getDimensions().y; j++){
            std::shared_ptr<Terrain> terrain = areaToSave->getMapTile(i, j);

            if(terrain != nullptr){
                result = saveTerrainObject(i, j, areaToSave->getMapTile(i, j), areaSaver->add_terrain());

                if(!result){
                    return false;
                }
            }
        }
    }

    return true;
}

bool WorldSaver::saveTerrainObject(int xLoc, int yLoc, const std::shared_ptr<Terrain> &terrain,
                                   world::Location_Area_Terrain *areaTerrainSaver) {
    bool result;

    try{
        areaTerrainSaver->set_xloc(xLoc);
        areaTerrainSaver->set_yloc(yLoc);
        areaTerrainSaver->set_ttype(terrain->getType());

        result = true;
    } catch (...){
        result = false;
    }

    return result;
}
