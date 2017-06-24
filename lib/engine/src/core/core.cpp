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
#include <iostream>

namespace MAIN {
    Core core;
}

Core::Core() {
    DICE_ROLLER = std::shared_ptr<DiceRoller>(new DiceRoller());

    itemList.reserve(0);
    monsterList.reserve(0);
    questList.reserve(0);
    locationList.reserve(0);
}

Core::~Core() {
    CleanUp();
    std::cout << "Core components cleaned up..." << std::endl;
}

std::shared_ptr<DiceRoller> Core::getDiceRoller() {
    return DICE_ROLLER;
}

std::shared_ptr<Monster> Core::GetCurrentMonster() {
    return currentMonster;
}

void Core::SetCurrentMonster(std::shared_ptr<Monster> monster) {
    currentMonster = monster;
}

std::shared_ptr<Player> Core::GetPlayer() {
    return player;
}

void Core::SetPlayer(Player _player) {
    player = std::make_shared<Player>(_player);
}

std::shared_ptr<Item> Core::ItemByID(int id) {
    if(itemList.size() > 0 && id >= 0){
        for(std::shared_ptr<Item> ptr : itemList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Monster> Core::MonsterByID(int id) {
    if(monsterList.size() > 0 && id >= 0){
        for(auto ptr : monsterList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Quest> Core::QuestByID(int id) {
    if(questList.size() > 0 && id >= 0){
        for(auto ptr : questList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

std::shared_ptr<Location> Core::LocationByID(int id) {
    if(locationList.size() > 0 && id >= 0){
        for(auto ptr : locationList){
            if(ptr->getID() == id){
                return ptr;
            }
        }
    }

    return nullptr;
}

void Core::CleanUp() {
    itemList.clear();
    monsterList.clear();
    questList.clear();
    locationList.clear();

    DICE_ROLLER.reset();
}
