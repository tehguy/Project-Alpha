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
#include <include/core/randomnumbergenerator.hpp>

namespace MAIN {
    Core core;
}

Core::Core() {

}

Core::~Core() {

}

void Core::init() {
    Screen scr;

    initColor(scr);

    scr.add("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");

    int ch = getch();

    game_map = std::shared_ptr<Frame>(new Frame(2 * scr.getHeight(), 2 * scr.getWidth(), 0, 0));
    game_viewport = std::shared_ptr<Frame>(new Frame(game_map, (scr.getHeight()/2) + 5, scr.getWidth(), 0, 0));

    stats_viewport = std::shared_ptr<FrameStats>(new FrameStats((scr.getHeight()/2) - 5, (scr.getWidth()/2) - 22, scr.getHeight()/2 + 5, 0));


    player = std::shared_ptr<Player>(new Player(game_map->getHeight() / 2, game_map->getWidth() / 2, 20));

    game_map->genPerlin(237);
    stats_viewport->genStatWindow();

    gameLoop(ch);
}

void Core::gameLoop(int ch) {
    if(ch == 'q' || ch == 'Q') return;

    game_map->add();
    game_viewport->center();
    game_viewport->refresh();
    stats_viewport->refresh();

    while(1){
        ch = getch();

        // Main character movements
        if(ch == KEY_LEFT) {
            game_map->add(player->getRow(), player->getCol() - 1);
            game_viewport->center();
            game_viewport->refresh();
        }
        else if(ch == KEY_RIGHT) {
            game_map->add(player->getRow(), player->getCol() + 1);
            game_viewport->center();
            game_viewport->refresh();
        }
        else if(ch == KEY_UP) {
            game_map->add(player->getRow() - 1, player->getCol());
            game_viewport->center();
            game_viewport->refresh();
        }
        else if(ch == KEY_DOWN) {
            game_map->add(player->getRow() + 1, player->getCol());
            game_viewport->center();
            game_viewport->refresh();
        }
        else if(ch == 'q' || ch == 'Q') {
            break;
        }
    }
}

void Core::initColor(Screen& scr) {
    if(!has_colors()){
        scr.add("Info: Your terminal does not support colors...\n\n");
    }
    else{
        init_pair(CORE::COLOR::BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(CORE::COLOR::GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(CORE::COLOR::YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair(CORE::COLOR::WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(CORE::COLOR::RED, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(CORE::COLOR::GREEN));
        scr.add("We have colors wooo!!\n\n");
        attroff(COLOR_PAIR(CORE::COLOR::GREEN));
    }
}

const std::shared_ptr<FrameStats> &Core::getStatWindow() {
    return stats_viewport;
}

const std::shared_ptr<Frame> &Core::getGameMap() {
    return game_map;
}

const std::shared_ptr<Player> &Core::getPlayer() {
    return player;
}
