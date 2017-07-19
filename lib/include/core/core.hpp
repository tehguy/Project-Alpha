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

#include <include/entity/player.hpp>
#include <include/world/location.hpp>

class Core {
public:
    void init();

private:
    void gameLoop();

    void movePlayer(int xOffset, int yOffset);
    void handleInput(int key);

    std::shared_ptr<Location> currentLocation;
};

namespace MAIN {
    extern Core core;
}