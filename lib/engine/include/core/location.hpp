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

#include <include/item/item.hpp>
#include <include/quests/quest.hpp>
#include <include/entity/monster.hpp>

class Location {
public:
    Location(int id, std::string in_name, std::string desc, int itemRequiredToEnter, int questAvailableHere,
    int monsterLivingHere, int locNorth, int locEast, int locSouth, int locWest);

    int getID();

    std::string getName();
    std::string getDescription();

    Item getItemRequiredToEnter();

    Quest getQuestAvailableHere();

    Monster getMonsterLivingHere();

    Location* getLocationToNorth();
    Location* getLocationToEast();
    Location* getLocationToSouth();
    Location* getLocationToWest();

private:

    int ID, itemRequiredToEnterID, questAvailableHereID, monsterLivingHereID, locNorthID, locEastID, locSouthID, locWestID;

    std::string name, description;
};