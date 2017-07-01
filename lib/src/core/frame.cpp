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

Frame::Frame(int nr_rows, int nr_cols, int row_0, int col_0) {
    _hasSuper = false;
    _super = nullptr;
    w = newwin(nr_rows, nr_cols, row_0, col_0);
    height = nr_rows;
    width = nr_cols;
    row = row_0;
    col = col_0;
}

Frame::Frame(const std::shared_ptr<Frame> &sw, int nr_rows, int nr_cols, int row_0, int col_0) {
    _hasSuper = true;
    _super = sw->win();
    w = derwin(sw->win(), nr_rows, nr_cols, row_0, col_0);
    height = nr_rows;
    width = nr_cols;
    row = row_0;
    col = col_0;
}

Frame::~Frame() {
    delwin(w);
}

WINDOW* Frame::win() {
    return w;
}

WINDOW* Frame::super() {
    return _super;
}

bool Frame::hasSuper() {
    return _hasSuper;
}

int Frame::getHeight() {
    return height;
}

int Frame::getWidth() {
    return width;
}

int Frame::getRow() {
    return row;
}

int Frame::getCol() {
    return col;
}

// Debug/Test function to see if your windows are how they should be
void Frame::fillWindow() {
    int max_x = width/2;
    int max_y = height/2;

    // Fill the first region with 0's
    for(int y = 0; y < max_y; ++y) {
        for(int x = 0; x < max_x; ++x) {
            mvwaddch(w, y, x, '0');
        }
    }

    // Fill the second region with 1's
    for(int y = 0; y < max_y; ++y) {
        for(int x = max_x; x < width; ++x) {
            mvwaddch(w, y, x, '1');
        }
    }

    // Fill the third region with 2's
    for(int y = max_y; y < height; ++y) {
        for(int x = 0; x < max_x; ++x) {
            mvwaddch(w, y, x, '2');
        }
    }

    // Fill the fourth region with 3's
    for(int y = max_y; y < height; ++y) {
        for(int x = max_x; x < width; ++x) {
            mvwaddch(w, y, x, '3');
        }
    }

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
}

void Frame::refresh() {
    if(_hasSuper){
        touchwin(_super);
    }
    wrefresh(w);
}

void Frame::move(int r, int c) {
    if(_hasSuper){
        mvderwin(w, r, c);
        row = r;
        col = c;
        refresh();
    }
}

void Frame::add() {
    mvwaddch_color(MAIN::core.getPlayer()->getRow(), MAIN::core.getPlayer()->getCol(),
                   MAIN::core.getPlayer()->getSymbol(), MAIN::core.getPlayer()->getSymbolColor());
}

void Frame::add(int row_0, int col_0) {
    if((row_0 >= 0 && row_0 < height) && (col_0 >= 0 && col_0 < width)){

        chtype target = mvwinch(w, row_0, col_0);

        if(has_colors()){
            if(target == CORE::CSYMBOL::CWATER || target == CORE::CSYMBOL::CWALL
               || target == CORE::CSYMBOL::CSNOW) return;
        }
        else{
            if(target == CORE::SYMBOL::WATER || target == CORE::SYMBOL::WALL || target == CORE::SYMBOL::SNOW) return;
        }

        erase();
        mvwaddch_color(row_0, col_0, MAIN::core.getPlayer()->getSymbol(), MAIN::core.getPlayer()->getSymbolColor());
        MAIN::core.getPlayer()->pos(row_0, col_0);
    }
}

void Frame::erase() {
    mvwaddch(w, MAIN::core.getPlayer()->getRow(), MAIN::core.getPlayer()->getCol(), ' ');
}

void Frame::center() {
    if(_hasSuper){
        int rr, cc, hh, ww;
        int _r = MAIN::core.getPlayer()->getRow() - height/2;
        int _c = MAIN::core.getPlayer()->getCol() - width/2;

        getmaxyx(_super, hh, ww);

        if(_c + width >= ww) {
            int delta = ww - (_c + width);
            cc = _c + delta;
        }
        else {
            cc = _c;
        }

        if(_r +height >= hh) {
            int delta = hh - (_r +height);
            rr = _r + delta;
        }
        else rr = _r;

        if (_r < 0) rr = 0;

        if (_c < 0) cc = 0;

        move(rr, cc);
    }
}

// Test function for use until actual location stuff is put in place
void Frame::genPerlin(const unsigned int &seed) {
    for(int i = 0; i < height; ++i) {     // y
        for(int j = 0; j < width; ++j) {  // x
            double x = (double)j/((double) width);
            double y = (double)i/((double) height);

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

void Frame::mvwaddch_color(int row_0, int col_0, const chtype symbol, const chtype csymbol) {
    if(has_colors()){
        mvwaddch(w, row_0, col_0, csymbol);
    }
    else{
        mvwaddch(w, row_0, col_0, symbol);
    }
}

void Frame::genStatWindow() {
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

    mvwaddch(w, height/2, 3, '[');
    mvwaddch(w, height/2, 14, ']');

    updateHealth();
}

void Frame::updateHealth() {

    float healthRatio = ((float)MAIN::core.getPlayer()->getCurHP() / (float)MAIN::core.getPlayer()->getMaxHP()) * 10;
    int col_0 = 4;

    for(int i = 0; i < 10; i++){
        mvwaddch(w, height/2, col_0 + i, ' ');
    }
    refresh();

    for(int i = 0; i < healthRatio; i++){
        mvwaddch_color(height/2, col_0 + i, '#', ('#' | COLOR_PAIR(CORE::COLOR::RED)));
    }
    refresh();
}
