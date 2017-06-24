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

#include <include/entity/monster.hpp>
#include <include/item/item.hpp>
#include <include/quests/quest.hpp>
#include <include/terrain/terrain.hpp>

#include <memory>

class Location {
public:
    Location(int id, std::string in_name, std::string desc, unsigned int _width, unsigned int _height,
             int itemRequiredToEnter, int questAvailableHere, int monsterLivingHere, int locNorth, int locEast,
             int locSouth, int locWest);

    ~Location();
    void initLinks();
    void addTerrain(Terrain terrain, unsigned int x_placement, unsigned int y_placement);
    std::shared_ptr<Terrain> getTerrainAtPosition(unsigned int row, unsigned int col);

    int getID();

    std::string getName();
    std::string getDescription();

    std::shared_ptr<Item> getItemRequiredToEnter();

    std::shared_ptr<Quest> getQuestAvailableHere();

    std::shared_ptr<Monster> getMonsterLivingHere();

    std::shared_ptr<Location> getLocationToNorth();
    std::shared_ptr<Location> getLocationToEast();
    std::shared_ptr<Location> getLocationToSouth();
    std::shared_ptr<Location> getLocationToWest();

private:
    void initTerrainVector(unsigned int _width, unsigned int _height);

    int ID;
    unsigned int width, height;

    int* tN = nullptr;
    int* tE = nullptr;
    int* tS = nullptr;
    int* tW = nullptr;

    std::shared_ptr<Location> locNorth, locEast, locSouth, locWest;
    std::shared_ptr<Item> itemRequiredToEnter;
    std::shared_ptr<Quest> questAvailableHere;
    std::shared_ptr<Monster> monsterLivingHere;

    std::vector<std::vector<std::shared_ptr<Terrain>>> terrainVector;

    std::string name, description;
};