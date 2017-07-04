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

#include <ncurses.h>

namespace STATS {
    enum ABS {
        STRENGTH,
        DEXTERITY,
        CONSTITUTION,
        INTELLIGENCE,
        WISDOM,
        CHARISMA
    };

    enum WEAPONTYPE {
        SIMPLE_MELEE,
        SIMPLE_RANGED,
        MARTIAL_MELEE,
        MARTIAL_RANGED
    };

    enum MONSTERPOOL {
        NUM_HIT_DICE,
        HIT_DIE_TYPE,
        HIT_DIE_MODIFIER,
        NUM_ATTACK_DICE,
        ATTACK_DIE_TYPE,
        ATTACK_DIE_MODIFIER
    };
}

namespace CORE {
    enum COLOR {
        BLUE = 1,
        GREEN,
        YELLOW,
        WHITE,
        RED
    };

    enum SYMBOL {
        PLAYER = '@',
        WATER = '~',
        WALL = '#',
        GRASS = '.',
        SNOW = 'S'
    };

    enum CSYMBOL {
        CPLAYER = (CORE::SYMBOL::PLAYER | COLOR_PAIR(CORE::COLOR::WHITE)),
        CWATER = (CORE::SYMBOL::WATER | COLOR_PAIR(CORE::COLOR::BLUE)),
        CWALL = (CORE::SYMBOL::WALL | COLOR_PAIR(CORE::COLOR::YELLOW)),
        CGRASS = (CORE::SYMBOL::GRASS | COLOR_PAIR(CORE::COLOR::GREEN)),
        CSNOW = (CORE::SYMBOL::SNOW | COLOR_PAIR(CORE::COLOR::WHITE)),
    };
}