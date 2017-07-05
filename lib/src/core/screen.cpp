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

#include <include/core/screen.hpp>
#include <include/enums/enums.hpp>

Screen::Screen() {
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    getmaxyx(stdscr, height, width);

    if(has_colors()){
        start_color();
        init_pair(CORE::COLOR::BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(CORE::COLOR::GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(CORE::COLOR::YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(CORE::COLOR::WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(CORE::COLOR::RED, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(CORE::COLOR::GREEN));
        add("We have colors wooo!!\n\n");
        attroff(COLOR_PAIR(CORE::COLOR::GREEN));
    }
    else {
        add("Info: Your terminal does not support colors...\n\n");
    }
}

Screen::~Screen() {
    endwin();
}

void Screen::add(const char *message) {
    printw(message);
    refresh();
}

void Screen::clearScreen() {
    clear();
    refresh();
}

int Screen::getHeight() {
    return height;
}

int Screen::getWidth() {
    return width;
}
