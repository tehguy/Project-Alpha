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

std::shared_ptr<Item> Location::getItemRequiredToEnter() {
    return CORE::WORLD.get()->ItemByID(itemRequiredToEnterID);
}

std::shared_ptr<Quest> Location::getQuestAvailableHere() {
    return CORE::WORLD.get()->QuestByID(questAvailableHereID);
}

std::shared_ptr<Monster> Location::getMonsterLivingHere() {
    return CORE::WORLD.get()->MonsterByID(monsterLivingHereID);
}

std::shared_ptr<Location> Location::getLocationToNorth() {
    return CORE::WORLD.get()->LocationByID(locNorthID);
}

std::shared_ptr<Location> Location::getLocationToEast() {
    return CORE::WORLD.get()->LocationByID(locEastID);
}

std::shared_ptr<Location> Location::getLocationToSouth() {
    return CORE::WORLD.get()->LocationByID(locSouthID);
}

std::shared_ptr<Location> Location::getLocationToWest() {
    return CORE::WORLD.get()->LocationByID(locWestID);
}
