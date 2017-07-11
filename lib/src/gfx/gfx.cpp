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
#include <include/gfx/gfx.hpp>

namespace GFX {
    sdl2::WindowShPtr screen = sdl2::WindowShPtr(nullptr);
    sdl2::RendererShPtr gRender = sdl2::RendererShPtr(nullptr);
    TileTexture gTileTexture;
    SDL_Rect camera;

    bool checkCollision(SDL_Rect a, SDL_Rect b) {
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

    bool initSDL() {
        if( (SDL_Init( SDL_INIT_VIDEO ) < 0) ){
            return false;
        }
        else {
            if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear" )){
                return false;
            }

            screen = sdl2::WindowShPtr(SDL_CreateWindow("CPPAdventures", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                             CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

            if(screen == nullptr){
                return false;
            }
            else {
                gRender = sdl2::RendererShPtr(SDL_CreateRenderer(GFX::screen.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
                if(gRender == nullptr){
                    return false;
                }
                else{
                    SDL_SetRenderDrawColor(gRender.get(), 0x0, 0x0, 0x0, 0x0);

                    int imgFlags = IMG_INIT_PNG;
                    if( !( IMG_Init(imgFlags) & imgFlags ) ){
                        return false;
                    }

                    if(!loadMedia()){
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool loadMedia() {
        if(!gTileTexture.loadFromFile("./lib/spritesheet.png")){
            printf("IMG Error: %s\n", IMG_GetError());
            return false;
        }

        return true;
    }
}