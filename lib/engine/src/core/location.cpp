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

#include <include/core/core.hpp>

Location::Location(int id, std::string in_name, std::string desc, unsigned int _width, unsigned int _height,
                   int itemRequiredToEnterID, int questAvailableHereID, int monsterLivingHereID, int locNorthID,
                   int locEastID, int locSouthID, int locWestID) {
    ID = id;
    name = in_name;
    description = desc;
    width = _width;
    height = _height;

    initTerrainVector(width, height);

    itemRequiredToEnter = MAIN::core.ItemByID(itemRequiredToEnterID);
    questAvailableHere = MAIN::core.QuestByID(questAvailableHereID);
    monsterLivingHere = MAIN::core.MonsterByID(monsterLivingHereID);
    tN = new int(locNorthID);
    tE = new int(locEastID);
    tS = new int(locSouthID);
    tW = new int(locWestID);
}

Location::~Location() {
    for(auto innerVec : terrainVector) {
        innerVec.clear();
    }

    terrainVector.clear();
}

void Location::initLinks() {
    locNorth = MAIN::core.LocationByID(*tN);
    locEast = MAIN::core.LocationByID(*tE);
    locSouth = MAIN::core.LocationByID(*tS);
    locWest = MAIN::core.LocationByID(*tW);

    delete tN;
    tN = nullptr;

    delete tE;
    tE = nullptr;

    delete tS;
    tS = nullptr;

    delete tW;
    tW = nullptr;
}

void Location::addTerrain(Terrain terrain, unsigned int row, unsigned int col) {
    if(row < height && col < width) {
        terrainVector.at(row).at(col) = std::make_shared<Terrain>(terrain);
    }
}

std::shared_ptr<Terrain> Location::getTerrainAtPosition(unsigned int row, unsigned int col) {
    if(row < height && col < width) {
        return terrainVector.at(row).at(col);
    }

    return nullptr;
}

void Location::initTerrainVector(unsigned int _width, unsigned int _height) {
    terrainVector.reserve(_height);
    for(unsigned int i = 0; i < _width; i++) {
        terrainVector.push_back(std::vector<std::shared_ptr<Terrain>>());
        terrainVector.at(i).reserve(_height);

        for(unsigned int j = 0; j < _height; j++) {
            terrainVector.at(i).push_back(nullptr);
        }
    }


}

int Location::getID() {
    return ID;
}

std::string Location::getName() {
    return name;
}

std::string Location::getDescription() {
    return description;
}

std::shared_ptr<Item> Location::getItemRequiredToEnter() {
    return itemRequiredToEnter;
}

std::shared_ptr<Quest> Location::getQuestAvailableHere() {
    return questAvailableHere;
}

std::shared_ptr<Monster> Location::getMonsterLivingHere() {
    return monsterLivingHere;
}

std::shared_ptr<Location> Location::getLocationToNorth() {
    return locNorth;
}

std::shared_ptr<Location> Location::getLocationToEast() {
    return locEast;
}

std::shared_ptr<Location> Location::getLocationToSouth() {
    return locSouth;
}

std::shared_ptr<Location> Location::getLocationToWest() {
    return locWest;
}
