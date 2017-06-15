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

#include <include/item/weapon.hpp>

Weapon::Weapon(int id, std::string name, std::string namePlural, STATS::WEAPONTYPE weapontype, STATS::ABS _attackStat,
               int numDice, int dieSides) : Item(id, name, namePlural) {
    type = weapontype;
    attackStat = _attackStat;
    numAttackDice = numDice;
    sidesOnDie = dieSides;
}

STATS::ABS Weapon::getAttackStat() {
    return attackStat;
}

int Weapon::getNumAttackDice() {
    return numAttackDice;
}

int Weapon::getSidesOnDie() {
    return sidesOnDie;
}
