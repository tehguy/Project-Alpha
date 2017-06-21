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

#include <include/system/dictionary.hpp>

Dictionary::Dictionary() {

}

Dictionary::~Dictionary() {
    functions.clear();
}

template<typename Function>
void Dictionary::add(std::string key, Function && function) {
    std::pair<std::string, Function &&> keypair(key, function);
    functions.insert(keypair);
}

void Dictionary::invoke(std::string key, std::string message) {
    functions.find(key)->second(message);
}
