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

#include <include/core/world.hpp>
#include <iostream>

World::World() {
    itemList.reserve(0);
    monsterList.reserve(0);
    questList.reserve(0);
    locationList.reserve(0);
}

World::~World() {
    CleanUp();
    std::cout << "World has been deleted..." << std::endl;
}

std::shared_ptr<Monster> World::GetCurrentMonster() {
    return currentMonster;
}

void World::SetCurrentMonster(std::shared_ptr<Monster> monster) {
    currentMonster = monster;
}

std::shared_ptr<Player> World::GetPlayer() {
    return player;
}

void World::SetPlayer(Player _player) {
    player = std::make_shared<Player>(_player);
}

std::shared_ptr<Item> World::ItemByID(int id) {
    if(itemList.size() > 0){
        for(std::shared_ptr<Item> ptr : itemList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Monster> World::MonsterByID(int id) {
    if(monsterList.size() > 0){
        for(auto ptr : monsterList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Quest> World::QuestByID(int id) {
    if(questList.size() > 0){
        for(auto ptr : questList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Location> World::LocationByID(int id) {
    if(locationList.size() > 0){
        for(auto ptr : locationList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

void World::CleanUp() {
    itemList.clear();
    monsterList.clear();
    questList.clear();
    locationList.clear();
}
