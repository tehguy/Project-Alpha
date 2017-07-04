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
    _super = sw;
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
    return _super->win();
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
        touchwin(super());
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

void Frame::erase() {
    unsigned int row_0 = MAIN::core.getPlayer()->getRow();
    unsigned int col_0 = MAIN::core.getPlayer()->getCol();

    std::vector<chtype> posSymbols = MAIN::core.getCurrentArea()->getMapSymbol(row_0, col_0);

    mvwaddch_color(row_0, col_0, posSymbols.at(0), posSymbols.at(1));
}

void Frame::center() {
    if(_hasSuper){
        int rr = 0, cc = 0, hh = 0, ww = 0;
        int _r = MAIN::core.getPlayer()->getRow() - height/2;
        int _c = MAIN::core.getPlayer()->getCol() - width/2;

        getmaxyx(super(), hh, ww);

        if(_c + width >= ww) {
            int delta = ww - (_c + width);
            cc = _c + delta;
        }
        else {
            cc = _c;
        }

        if(_r + height >= hh) {
            int delta = hh - (_r + height);
            rr = _r + delta;
        }
        else {
            rr = _r;
        }

        if (_r < 0) rr = 0;

        if (_c < 0) cc = 0;

        move(rr, cc);
    }
}

void Frame::resize(unsigned int r, unsigned int c) {
    wresize(w, r, c);
    height = r;
    width = c;
}

void Frame::mvwaddch_color(int row_0, int col_0, const chtype symbol, const chtype csymbol) {
    if(has_colors()){
        mvwaddch(w, row_0, col_0, csymbol);
    }
    else{
        mvwaddch(w, row_0, col_0, symbol);
    }
}

void Frame::blankView() {
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            mvwaddch(w, i, j, ' ');
        }
    }
}
