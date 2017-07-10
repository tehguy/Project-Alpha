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
#include <include/core/constants.hpp>
#include <include/core/core.hpp>

namespace MAIN {
    Core core;
}

Core::Core() {

}

Core::~Core() {

}

void Core::init() {
    if(!GFX::initSDL()){
        return;
    }

    GFX::camera = {0, 0, CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT};

    player = std::shared_ptr<Player>(new Player(25, 25, 20));

    currentArea = std::shared_ptr<Area>(new Area("test", 50, 50));
    currentArea->genRandom(237);
    currentArea->setEntitySymbol(25, 25, *player);

    gameLoop();
    close();
}

void Core::close() {
    IMG_Quit();
    SDL_Quit();
}

void Core::gameLoop() {
    bool quit = false;

    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_q:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(GFX::gRender.get(), 0x0, 0x0, 0x0, 0x0);
        SDL_RenderClear(GFX::gRender.get());

        currentArea->draw();

        SDL_RenderPresent(GFX::gRender.get());
    }
}

const std::shared_ptr<Player> &Core::getPlayer() {
    return player;
}

const std::shared_ptr<Area> &Core::getCurrentArea() {
    return currentArea;
}