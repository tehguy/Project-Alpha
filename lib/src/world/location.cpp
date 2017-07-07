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

#include <include/world/location.hpp>

Location::Location() {
    nullArea = nullptr;
}

void Location::addArea(std::shared_ptr<Area> area) {
    areas.push_back(area);
}

std::shared_ptr<Area>& Location::getSubLocation(std::string identifier) {
    for(auto& loc : areas){
        if(loc->getIdentifier() == identifier){
            return loc;
        }
    }

    return nullArea;
}
