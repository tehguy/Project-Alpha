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

#include <include/entity/monster.hpp>

Monster::Monster(int id, std::string name, int rewardExp, int rewardG, std::vector<int> dicePool,
                 std::vector<int> stats) : Entity(stats) {

}

int Monster::getID() {
    return ID;
}

int Monster::getRewardExperience() {
    return rewardExperience;
}

int Monster::getRewardGold() {
    return rewardGold;
}

std::string Monster::getName() {
    return name;
}

std::vector<LootItem> *Monster::getLootTable() {
    std::vector<LootItem>* temp(&lootTable);

    return temp;
}
