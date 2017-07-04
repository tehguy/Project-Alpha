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
#include <cmath>

FrameStats::FrameStats(int nr_rows, int nr_cols, int row_0, int col_0) : Frame(nr_rows, nr_cols, row_0, col_0) {}

void FrameStats::genStatWindow() {
    for(int y = 0; y < height; ++y) {
        mvwaddch(w, y, 0, '|');
        mvwaddch(w, y, width - 1, '|');
    }

    for(int x = 0; x < width; ++x) {
        mvwaddch(w, 0, x, '-');
        mvwaddch(w, height - 1, x, '-');
    }

    mvwaddch(w, 0, 0, '+');
    mvwaddch(w, 0, width-1, '+');
    mvwaddch(w, height-1, 0, '+');
    mvwaddch(w, height-1, width-1, '+');

    mvwaddch(w, (height/2) - 1, 3, '[');
    mvwaddch(w, (height/2) - 1, 14, ']');

    mvwaddch(w, (height/2) + 1, 3, '[');
    mvwaddch(w, (height/2) + 1, 14, ']');

    updateHealth();
    updateExperience();
}

void FrameStats::updateHealth() {
    updateStatsBar(-1, MAIN::core.getPlayer()->getCurHP(), MAIN::core.getPlayer()->getMaxHP(), CORE::COLOR::RED);
}

void FrameStats::updateExperience() {
    updateStatsBar(1, MAIN::core.getPlayer()->getCurExp(), MAIN::core.getPlayer()->getExpToNextLevel(), CORE::COLOR::GREEN);
}

void FrameStats::updateStatsBar(int rowOffset, unsigned int current, unsigned int max, int color) {
    float ratio = std::floor(((float)current / (float)max) * 10);
    int col_0 = 4;

    // Clear the current bar
    for(int i = 0; i < 10; i++){
        mvwaddch(w, (height/2) + rowOffset, col_0 + i, ' ');
    }

    for(int i = 0; i < ratio; i++){
        mvwaddch_color((height/2) + rowOffset, col_0 + i, '#', ('#' | COLOR_PAIR(color)));
    }
    refresh();
}
