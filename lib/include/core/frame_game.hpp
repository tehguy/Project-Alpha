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

#include <include/core/frame.hpp>

class FrameGame : public Frame {
public:
    FrameGame(int nr_rows, int nr_cols, int row_0, int col_0);

    void drawArea(Area& area);
    void genAreaWithPerlin(Area& area, const unsigned int &seed);

    void genPerlin(const unsigned int &seed);

    void add();
    void add(unsigned int row_0, unsigned int col_0);
};