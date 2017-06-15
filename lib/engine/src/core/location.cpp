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
#include <include/core/world.hpp>

Location::Location(int id, std::string in_name, std::string desc, int itemRequiredToEnter, int questAvailableHere,
                   int monsterLivingHere, int locNorth, int locEast, int locSouth, int locWest) {
    ID = id;
    name = in_name;
    description = desc;
    itemRequiredToEnterID = itemRequiredToEnter;
    questAvailableHereID = questAvailableHere;
    monsterLivingHereID = monsterLivingHere;
    locNorthID = locNorth;
    locEastID = locEast;
    locSouthID = locSouth;
    locWestID = locWest;
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

Item Location::getItemRequiredToEnter() {
    return World::ItemByID(itemRequiredToEnterID);
}

Quest Location::getQuestAvailableHere() {
    return World::QuestByID(questAvailableHereID);
}

Monster Location::getMonsterLivingHere() {
    return World::MonsterByID(monsterLivingHereID);
}

Location* Location::getLocationToNorth() {
    return World::LocationByID(locNorthID);
}

Location* Location::getLocationToEast() {
    return World::LocationByID(locEastID);
}

Location* Location::getLocationToSouth() {
    return World::LocationByID(locSouthID);
}

Location* Location::getLocationToWest() {
    return World::LocationByID(locWestID);
}
