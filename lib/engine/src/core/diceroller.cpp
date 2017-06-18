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

#include <algorithm>
#include <include/core/diceroller.hpp>
#include <include/core/randomnumbergenerator.hpp>

int DiceRoller::RollDice(int numberOfDice, int sidesOnDie, int modifier){
    return RandomNumberGenerator::rollDice(numberOfDice, (numberOfDice * sidesOnDie)) + modifier;
}

int DiceRoller::RollAbilityScore(int numberOfDice) {
    std::vector<int> rollList;
    rollList.reserve(3);

    for(int i = 0; i < numberOfDice; i++){
        rollList.push_back(RandomNumberGenerator::rollDice(1, 6));
    }

    if(numberOfDice == 2){
        rollList.push_back(6);
    }

    std::sort(rollList.rbegin(), rollList.rend());

    return rollList.at(0) + rollList.at(1) + rollList.at(2);
}