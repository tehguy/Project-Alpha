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

#include <SDL2/SDL_image.h>

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

    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    currentArea = std::shared_ptr<Area>(new Area("test", 50, 50));
    currentArea->genRandom();

    gameLoop();
    close();
}

void Core::close() {
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
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
        SDL_SetRenderDrawColor(gRender.get(), 0x0, 0x0, 0x0, 0x0);
        SDL_RenderClear(gRender.get());

        currentArea->draw();

        SDL_RenderPresent(gRender.get());
    }
}

const std::shared_ptr<Player> &Core::getPlayer() {
    return player;
}

const std::shared_ptr<Area> &Core::getCurrentArea() {
    return currentArea;
}

bool Core::initSDL() {
    if( (SDL_Init( SDL_INIT_VIDEO ) < 0) ){
        return false;
    }
    else {
        if(TTF_Init() < 0){
            printf("TTF error: %s\n", TTF_GetError());
            return false;
        }
        else{
            font = TTF_OpenFont("./lib/Cuprum-Regular.ttf", MAIN::TEXT_SIZE);
            if(!font){
                printf("TTF_Openfont: %s\n", TTF_GetError());
            }
        }

        if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" )){
            return false;
        }

        screen = sdl2::WindowShPtr(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

        if(screen == nullptr){
            return false;
        }
        else {
            gRender = sdl2::RendererShPtr(SDL_CreateRenderer(screen.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
            if(gRender == nullptr){
                return false;
            }
            else{
                SDL_SetRenderDrawColor(gRender.get(), 0x0, 0x0, 0x0, 0x0);

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init(imgFlags) & imgFlags ) ){
                    return false;
                }
            }
        }
    }

    return true;
}

const sdl2::RendererShPtr &Core::getRenderer() {
    return gRender;
}

SDL_Rect &Core::getCamrea() {
    return camera;
}

TileTexture &Core::getTileTexture() {
    return gTileTexture;
}

bool Core::checkCollision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    return leftA < rightB;

}

TTF_Font *Core::getFont() {
    return font;
}
