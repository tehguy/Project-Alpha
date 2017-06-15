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

#include <include/item/healingpotion.hpp>

HealingPotion::HealingPotion(int id, std::string name, std::string namePlural,
                             int numHeal, int dieSides, int mod) : Item(id, name, namePlural){
    numberOfHealDice = numHeal;
    sidesOnDie = dieSides;
    modifier = mod;
}

int HealingPotion::getNumberOfHealDice() {
    return numberOfHealDice;
}

int HealingPotion::getSidesOnDie() {
    return sidesOnDie;
}

int HealingPotion::getModifier() {
    return modifier;
}
