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

#include <include/entity/player.hpp>

Player::Player(int chp, int mhp, std::vector<int> stats) : Entity(chp, mhp, stats) {
    gold = 0;
    expPoints = 0;
    level = 0;

    currentLocation = nullptr;
    inventory = std::make_shared<std::vector<InventoryItem>>();
    quests = std::make_shared<std::vector<PlayerQuest>>();
}

int Player::getGold() {
    return gold;
}

int Player::getExpPoints() {
    return expPoints;
}

int Player::getLevel() {
    return level;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::addExpPoints(int amount) {
    expPoints += amount;
}

void Player::setCurrentLocation(std::shared_ptr<Location> location) {
    currentLocation = location;
}

std::shared_ptr<Location> Player::getCurrentLocation() {
    return currentLocation;
}

void Player::addItemToInventory(int itemToAddID) {
    if(inventory->size() > 0){
        for(InventoryItem item : *inventory){
            if(item.getDetails()->getID() == itemToAddID){
                item.incrementQuantity();
                return;
            }
        }
    }
    InventoryItem tmpItem(itemToAddID, 1);

    if(tmpItem.getDetails() == nullptr){
        printf("oh no\n");
    }

    inventory->push_back(tmpItem);
}

std::shared_ptr<std::vector<InventoryItem>> Player::getInventory() {
    return inventory;
}

std::shared_ptr<std::vector<PlayerQuest>> Player::getQuests() {
    return quests;
}
