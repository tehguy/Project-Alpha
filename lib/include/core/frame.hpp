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

#include <memory>
#include <ncurses.h>

#include <include/entity/player.hpp>
#include <include/world/area.hpp>

class Frame {
public:
    Frame(int nr_rows, int nr_cols, int row_0, int col_0);
    Frame(const std::shared_ptr<Frame> &sw, int nr_rows, int nr_cols, int row_0, int col_0);
    ~Frame();

    WINDOW* win();
    WINDOW* super();
    
    bool hasSuper();

    int getHeight();
    int getWidth();
    int getRow();
    int getCol();

    void fillWindow();
    void refresh();
    void move(int r, int c);
    void erase();
    void center();
    void resize(unsigned int r, unsigned int c);

    void mvwaddch_color(int row_0, int col_0, const chtype symbol, const chtype color);


protected:
    void blankView();

    int height, width, row, col;

    WINDOW* w;
    std::shared_ptr<Frame> _super;

    bool _hasSuper;
};