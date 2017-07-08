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
#include <include/core/randomnumbergenerator.hpp>

namespace MAIN {
    Core core;
}

Core::Core() {

}

Core::~Core() {

}

void Core::init() {
    if(!initSDL()){
        return;
    }

    gameLoop();

    SDL_DestroyWindow(screen.get());
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
    }
}

const std::shared_ptr<Player> &Core::getPlayer() {
    return player;
}

const std::shared_ptr<Area> &Core::getCurrentArea() {
    return currentArea;
}

bool Core::initSDL() {
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1){
        return false;
    }

    screen = sdl2::WindowShPtr(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN));

    if(screen == nullptr){
        return false;
    }
    else {
        screenSurface = sdl2::SurfaceShPtr(SDL_GetWindowSurface(screen.get()));

        SDL_UpdateWindowSurface(screen.get());
    }

    return true;
}
