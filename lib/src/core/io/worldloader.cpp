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

#include <include/core/io/worldloader.hpp>

#include <include/world/terrain/grass.hpp>
#include <include/world/terrain/snow.hpp>
#include <include/world/terrain/mountain.hpp>
#include <include/world/terrain/water.hpp>

#include <iostream>

WorldLoader::WorldLoader() : FileIO() {

}

std::shared_ptr<Location> WorldLoader::loadLocation() {
    std::string fileName = "./save/test.map";

    std::shared_ptr<Location> loadedLocation = std::shared_ptr<Location>(nullptr);

    if(openFile(fileName, &fileReader)){
        WORLD::Location locationLoader;
        bool eof;

        google::protobuf::io::IstreamInputStream inputStream(&fileReader);
        google::protobuf::util::ParseDelimitedFromZeroCopyStream(&locationLoader, &inputStream, &eof);

        std::string name = locationLoader.name();
        int xDim = locationLoader.width();
        int yDim = locationLoader.height();

        int currentAreaX = locationLoader.current_area_x();
        int currentAreaY = locationLoader.current_area_y();

        loadedLocation = std::shared_ptr<Location>(new Location(name, xDim, yDim));

        loadArea(locationLoader, loadedLocation);

        closeFile(&fileReader);

        loadedLocation->setCurrentArea(currentAreaX, currentAreaY);
    }

    return loadedLocation;
}

void WorldLoader::loadArea(WORLD::Location &locationLoader,
                           std::shared_ptr<Location> &loadedLocation) {
    for(int i = 0; i < locationLoader.areas().size(); i++){
        const WORLD::Area& areaLoader = locationLoader.areas(i);
        Area area(areaLoader.name());

        loadTerrain(areaLoader, area);

        loadedLocation->placeArea(areaLoader.xloc(), areaLoader.yloc(), area);
    }
}

void WorldLoader::loadTerrain(const WORLD::Area &areaLoader, Area &loadedArea) {
    std::shared_ptr<Terrain> loadedTerrain;
    std::shared_ptr<Tile> loadedTile = std::shared_ptr<Tile>(new Tile());

    for(int i = 0; i < areaLoader.tile().size(); i++){
        int xLoc = areaLoader.tile(i).terrain().xloc();
        int yLoc = areaLoader.tile(i).terrain().yloc();
        int ttype = areaLoader.tile(i).terrain().ttype();

        switch(ttype){
            case 1:
                loadedTile->setTerrain(std::shared_ptr<Terrain>(new Grass(xLoc, yLoc)));
                break;
            case 2:
                loadedTile->setTerrain(std::shared_ptr<Terrain>(new Water(xLoc, yLoc)));
                break;
            case 3:
                loadedTile->setTerrain(std::shared_ptr<Terrain>(new Mountain(xLoc, yLoc)));
                break;
            case 4:
                loadedTile->setTerrain(std::shared_ptr<Terrain>(new Snow(xLoc, yLoc)));
                break;
            default:
                loadedTile->setTerrain(nullptr);
                break;
        }

        loadedArea.setMapTile(xLoc, yLoc, loadedTile);
    }
}
