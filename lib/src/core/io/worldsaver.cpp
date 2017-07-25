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

#include <include/core/io/worldsaver.hpp>

WorldSaver::WorldSaver() : FileIO(){

}

bool WorldSaver::saveLocation(const std::shared_ptr<Location> &locationToSave) {
    if(locationToSave == nullptr){
        return false;
    }

    bool result = false;

    std::string locName = locationToSave->getName();
    std::string saveFileName = "./save/test.map";

    if(openFile(saveFileName, &saveWriter)){
        world::Location locationSaver;

        int width = locationToSave->getDimensions().x;
        int height = locationToSave->getDimensions().y;

        int currentAreaX = locationToSave->getCurrentArea()->getLocationalPosition().x;
        int currentAreaY = locationToSave->getCurrentArea()->getLocationalPosition().y;

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

        locationSaver.set_current_area_x(currentAreaX);
        locationSaver.set_current_area_y(currentAreaY);

        result = google::protobuf::util::SerializeDelimitedToOstream(locationSaver, &saveWriter);

        closeFile(&saveWriter);
    }

    return result;
}

bool WorldSaver::saveArea(const std::shared_ptr<Area> &areaToSave, world::Location::Area *areaSaver) {
    if(areaToSave == nullptr){
        return true;
    }

    areaSaver->set_name(areaToSave->getAreaName());

    int x = areaToSave->getLocationalPosition().x;
    int y = areaToSave->getLocationalPosition().y;

    areaSaver->set_xloc(x);
    areaSaver->set_yloc(y);

    bool result;

    for(int i = 0; i < areaToSave->getDimensions().x; i++){
        for(int j = 0; j < areaToSave->getDimensions().y; j++){
            std::shared_ptr<Terrain> terrain = areaToSave->getMapTile(i, j);

            result = saveTerrainObject(i, j, terrain, areaSaver->add_terrain());

            if(!result){
                return false;
            }
        }
    }

    return true;
}

bool WorldSaver::saveTerrainObject(int xLoc, int yLoc, const std::shared_ptr<Terrain> &terrain,
                                   world::Location::Area::Terrain *areaTerrainSaver) {
    bool result;

    try{
        areaTerrainSaver->set_xloc(xLoc);
        areaTerrainSaver->set_yloc(yLoc);

        if(terrain != nullptr){
            areaTerrainSaver->set_ttype(terrain->getType());
        }
        else{
            areaTerrainSaver->set_ttype(0);
        }

        result = true;
    } catch (...){
        result = false;
    }

    return result;
}
