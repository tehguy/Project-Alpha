/*
    Project Alpha
    Copyright (C) 2017  Pixima Development

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

#include <include/core/io/worldloader.hpp>
#include <include/core/io/worldsaver.hpp>

#include <include/entity/player.hpp>
#include <include/gfx/gfx.hpp>
#include <include/world/location.hpp>


class Core {
public:
    int init();

private:
    void gameLoop();

    void handleInput(int key);

    void draw();

    void movePlayer(int xOffset, int yOffset);

    void genTestArea();

    void setCurrentLocation(const std::shared_ptr<Location> location);
    const std::shared_ptr<Location> getCurrentLocation();

    std::shared_ptr<Location> currentLocation;

    WorldLoader worldLoader;
    WorldSaver worldSaver;
};

namespace MAIN {
    extern Core core;
}