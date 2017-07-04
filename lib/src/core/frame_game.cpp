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
#include <include/core/perlinnoise.hpp>

#include <include/world/terrain/grass.hpp>
#include <include/world/terrain/snow.hpp>
#include <include/world/terrain/wall.hpp>
#include <include/world/terrain/water.hpp>

FrameGame::FrameGame(int nr_rows, int nr_cols, int row_0, int col_0) : Frame(nr_rows, nr_cols, row_0, col_0) {

}

void FrameGame::drawArea(Area &area) {
    blankView();
    resize(area.getHeight(), area.getWidth());

    for(unsigned int r = 0; r < area.getHeight(); r++) {
        for(unsigned int c = 0; c < area.getWidth(); c++) {
            std::vector<chtype> symbols = area.getMapSymbol(r, c);

            mvwaddch_color(r, c, symbols.at(0), symbols.at(1));
        }
    }
}

// Test function for use until actual world stuff is put in place
void FrameGame::genAreaWithPerlin(Area &area, const unsigned int &seed) {
    for(unsigned int i = 0; i < area.getHeight(); ++i) {     // y
        for(unsigned int j = 0; j < area.getWidth(); ++j) {  // x
            double x = (double)j/((double) area.getWidth());
            double y = (double)i/((double) area.getHeight());

            double n = PerlinNoise::NoiseWithSeed(seed, 10 * x, 10 * y, 0.8);

            // Watter (or a Lakes)
            if(n < 0.35) {
                area.setMapSymbol(i, j, Water());
            }
                // Floors (or Planes)
            else if (n >= 0.35 && n < 0.6) {
                area.setMapSymbol(i, j, Grass());
            }
                // Walls (or Mountains)
            else if (n >= 0.6 && n < 0.8) {
                area.setMapSymbol(i, j, Wall());
            }
                // Ice (or Snow)
            else {
                area.setMapSymbol(i, j, Snow());
            }
        }
    }
}

// Test function for use until actual world stuff is put in place
void FrameGame::genPerlin(const unsigned int &seed) {
    for(int i = 0; i < getHeight(); ++i) {     // y
        for(int j = 0; j < getWidth(); ++j) {  // x
            double x = (double)j/((double) getWidth());
            double y = (double)i/((double) getHeight());

            double n = PerlinNoise::NoiseWithSeed(seed, 10 * x, 10 * y, 0.8);

            // Watter (or a Lakes)
            if(n < 0.35) {
                mvwaddch_color(i, j, CORE::SYMBOL::WATER, CORE::CSYMBOL::CWATER);
            }
                // Floors (or Planes)
            else if (n >= 0.35 && n < 0.6) {
                mvwaddch_color(i, j, CORE::SYMBOL::GRASS, CORE::CSYMBOL::CGRASS);
            }
                // Walls (or Mountains)
            else if (n >= 0.6 && n < 0.8) {
                mvwaddch_color(i, j, CORE::SYMBOL::WALL, CORE::CSYMBOL::CWALL);
            }
                // Ice (or Snow)
            else {
                mvwaddch_color(i, j, CORE::SYMBOL::SNOW, CORE::CSYMBOL::CSNOW);
            }
        }
    }
}

void FrameGame::add() {
    mvwaddch_color(MAIN::core.getPlayer()->getRow(), MAIN::core.getPlayer()->getCol(),
                   MAIN::core.getPlayer()->getSymbol(), MAIN::core.getPlayer()->getSymbolColor());
}

void FrameGame::add(unsigned int row_0, unsigned int col_0) {
    if((row_0 >= 0 && row_0 < getHeight()) && (col_0 >= 0 && col_0 < getWidth())){

        chtype target = MAIN::core.getCurrentArea()->getMapTerrain(row_0, col_0).getSymbol();

        if(target == CORE::SYMBOL::WATER || target == CORE::SYMBOL::WALL
           || target == CORE::SYMBOL::SNOW) return;

        erase();
        mvwaddch_color(row_0, col_0, MAIN::core.getPlayer()->getSymbol(), MAIN::core.getPlayer()->getSymbolColor());
        MAIN::core.getPlayer()->pos(row_0, col_0);
    }
}