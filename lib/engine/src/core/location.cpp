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

#include <include/core/location.hpp>
#include <include/core/core.hpp>

Location::Location(int id, std::string in_name, std::string desc, int itemRequiredToEnterID, int questAvailableHereID,
                   int monsterLivingHereID, int locNorthID, int locEastID, int locSouthID, int locWestID) {
    ID = id;
    name = in_name;
    description = desc;
    itemRequiredToEnter = MAIN::core.getWorld()->ItemByID(itemRequiredToEnterID);
    questAvailableHere = MAIN::core.getWorld()->QuestByID(questAvailableHereID);
    monsterLivingHere = MAIN::core.getWorld()->MonsterByID(monsterLivingHereID);
    *tN = locNorthID;
    *tE = locEastID;
    *tS = locSouthID;
    *tW = locWestID;
}

Location::~Location(){}

void Location::initLinks() {
    locNorth = MAIN::core.getWorld()->LocationByID(*tN);
    locEast = MAIN::core.getWorld()->LocationByID(*tE);
    locSouth = MAIN::core.getWorld()->LocationByID(*tS);
    locWest = MAIN::core.getWorld()->LocationByID(*tW);

    delete tN;
    tN = nullptr;

    delete tE;
    tE = nullptr;

    delete tS;
    tS = nullptr;

    delete tW;
    tW = nullptr;
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
