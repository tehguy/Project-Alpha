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

#include "entity.hpp"

#include <include/core/location.hpp>
#include <include/item/inventoryitem.hpp>
#include <include/quests/playerquest.hpp>

class Player : public Entity{
public:
    Player(int chp, int mhp, std::vector<int> stats);

    int getGold();
    int getExpPoints();
    int getLevel();

    void addGold(int amount);
    void addExpPoints(int amount);

    void setCurrentLocation(std::shared_ptr<Location> location);
    std::shared_ptr<Location> getCurrentLocation();

    void addItemToInventory(int itemToAddID);
    std::shared_ptr<std::vector<InventoryItem>> getInventory();

    std::shared_ptr<std::vector<PlayerQuest>> getQuests();
private:

    int gold, expPoints, level;

    std::shared_ptr<Location> currentLocation;
    std::shared_ptr<std::vector<InventoryItem>> inventory;
    std::shared_ptr<std::vector<PlayerQuest>> quests;
};