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

#include <include/world/terrain/terrain.hpp>

Terrain::Terrain(chtype _symbol, chtype _csymbol) {
    symbol = _symbol;
    csymbol = _csymbol;
}

chtype Terrain::getSymbol() const {
    return symbol;
}

chtype Terrain::getCSymbol() const {
    return csymbol;
}

const std::vector <chtype, std::allocator<chtype>> Terrain::getTerrainSymbols() {
    return {symbol, csymbol};
}