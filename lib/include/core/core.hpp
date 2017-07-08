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

#include <include/core/sdl_structs.hpp>
#include <include/entity/player.hpp>
#include <include/world/location.hpp>

class Core {
public:
    Core();
    ~Core();

    void init();

    const std::shared_ptr<Player>& getPlayer();

    const std::shared_ptr<Area>& getCurrentArea();

private:
    void gameLoop();
    bool initSDL();

    sdl2::WindowShPtr screen;
    sdl2::SurfaceShPtr screenSurface;

    std::shared_ptr<Player> player;

    std::shared_ptr<Area> currentArea;
};

namespace MAIN {
    extern Core core;
}