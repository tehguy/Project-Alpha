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

#include <include/item/lootitem.hpp>
#include <include/core/core.hpp>

LootItem::LootItem(int id, int dropPer, bool isDef) {
    ID = id;
    dropPercentage = dropPer;
    isDefault = isDef;
}

Item *LootItem::getDetails() {
    return CORE::WORLD->ItemByID(ID);
}

void LootItem::setDetails(int id) {
    ID = id;
}

int LootItem::getDropPercentage() {
    return dropPercentage;
}

void LootItem::setDropPercentage(int dropPer) {
    dropPercentage = dropPer;
}

bool LootItem::isDefaultItem() {
    return isDefault;
}

void LootItem::setDefaultItem(bool isDef) {
    isDefault = isDef;
}
