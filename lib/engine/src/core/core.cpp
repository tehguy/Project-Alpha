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
#include <ncurses.h>

#include <include/core/core.hpp>
#include <include/core/screen.hpp>

namespace MAIN {
    Core core;
}

Core::Core() {

}

Core::~Core() {

}

void Core::init() {
    Screen scr;

    if(!has_colors()){
        scr.add("Warning: terminal does not support colors...\n\n");
    }
    else{
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_WHITE, COLOR_BLACK);

        attron(COLOR_PAIR(2));
        scr.add("We have colors wooo!!\n\n");
        attroff(COLOR_PAIR(2));
    }

    scr.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");

    int ch = getch();

    Frame game_map(2 * scr.getHeight(), 2 * scr.getWidth(), 0, 0);
    Frame viewport(game_map, scr.getHeight(), scr.getWidth(), 0, 0);

    Player player('@', game_map.getHeight() / 2, game_map.getWidth() / 2);

    game_map.genPerlin(237);

    gameLoop(game_map, viewport, player, ch);
}

void Core::gameLoop(Frame &game_map, Frame &viewport, Player &player, int ch) {
    if(ch == 'q' || ch == 'Q') return;

    game_map.add(player);
    viewport.center(player);
    viewport.refresh();

    while(1){
        ch = getch();

        // Main character movements
        if(ch == KEY_LEFT) {
            game_map.add(player, player.getRow(), player.getCol() - 1);
            viewport.center(player);
            viewport.refresh();
        }
        else if(ch == KEY_RIGHT) {
            game_map.add(player, player.getRow(), player.getCol() + 1);
            viewport.center(player);
            viewport.refresh();
        }
        else if(ch == KEY_UP) {
            game_map.add(player, player.getRow() - 1, player.getCol());
            viewport.center(player);
            viewport.refresh();
        }
        else if(ch == KEY_DOWN) {
            game_map.add(player, player.getRow() + 1, player.getCol());
            viewport.center(player);
            viewport.refresh();
        }
        else if(ch == 'q' || ch == 'Q') {
            break;
        }
    }
}
