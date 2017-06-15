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

World::World() {

}

World::~World() {
    currentMonster = nullptr;

    for(auto* ptr : monsterList){
        delete ptr;
        ptr = nullptr;
    }
    monsterList.clear();
}

Monster *World::getCurrentMonster() {
    return currentMonster;
}

void World::setCurrentMonster(Monster* monster) {
    currentMonster = monster;
}

Item *World::ItemByID(int id) {
    for(auto* ptr : itemList){
        if(ptr->getID() == id){
            return ptr;
        }
    }

    return nullptr;
}

Monster *World::MonsterByID(int id) {
    for(auto* ptr : monsterList){
        if(ptr->getID() == id){
            return ptr;
        }
    }

    return nullptr;
}