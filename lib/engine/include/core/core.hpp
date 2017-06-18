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

#include <include/core/diceroller.hpp>
#include <include/core/randomnumbergenerator.hpp>
#include <include/core/world.hpp>
#include <memory>

class Core {
public:
    Core();
    ~Core();

    std::shared_ptr<World> getWorld();
    std::shared_ptr<DiceRoller> getDiceRoller();

private:
    static std::shared_ptr<World> WORLD;
    std::shared_ptr<DiceRoller> DICE_ROLLER;
};

namespace MAIN{
    static Core core;
}