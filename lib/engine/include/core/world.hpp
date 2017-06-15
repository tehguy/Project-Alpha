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

#include "location.hpp"

#include <include/entity/monster.hpp>
#include <include/entity/player.hpp>

#include <include/item/item.hpp>

#include <memory>

class World {
public:

    World();
    ~World();

    Monster* GetCurrentMonster();
    void SetCurrentMonster(Monster &monster);

    Player* GetPlayer();
    void SetPlayer(Player &_player);

    Item* ItemByID(int id);
    Monster* MonsterByID(int id);
    Quest* QuestByID(int id);
    Location* LocationByID(int id);

    void CleanUp();
private:

    Player* player;

    std::vector<Item*> itemList;
    std::vector<Monster*> monsterList;
    std::vector<Quest*> questList;
    std::vector<Location*> locationList;

    Monster* currentMonster;
};