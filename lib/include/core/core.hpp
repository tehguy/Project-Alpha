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

#include <include/core/frame_stats.hpp>
#include <include/core/screen.hpp>

#include <include/entity/player.hpp>

#include <include/world/location.hpp>

#include <memory>

class Core {
public:
    Core();
    ~Core();

    void init();
    void initColor(Screen& scr);

    const std::shared_ptr<FrameStats>& getStatWindow();
    const std::shared_ptr<Frame>& getGameMap();

    const std::shared_ptr<Player>& getPlayer();

private:
    void gameLoop(int ch);

    std::shared_ptr<Frame> game_map;
    std::shared_ptr<Frame> game_viewport;
    std::shared_ptr<FrameStats> stats_viewport;

    std::shared_ptr<Player> player;
};

namespace MAIN {
    extern Core core;
}