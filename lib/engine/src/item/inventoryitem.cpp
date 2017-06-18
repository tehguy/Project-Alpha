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

InventoryItem::InventoryItem(int id, int quant) {
    details = MAIN::core.getWorld()->ItemByID(id);
    quantity = quant;
}

std::shared_ptr<Item> InventoryItem::getDetails() {
    return details;
}

void InventoryItem::setDetails(int id) {
    details = MAIN::core.getWorld()->ItemByID(id);
}

int InventoryItem::getQuantity() {
    return quantity;
}

void InventoryItem::setQuantity(int quant) {
    quantity = quant;
}

void InventoryItem::incrementQuantity() {
    setQuantity(quantity + 1);
}
