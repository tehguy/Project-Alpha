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

#include <include/core/sdl_structs.hpp>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

class TileTexture {
public:
    TileTexture();
    ~TileTexture();

    bool loadFromFile(std::string path);
    //bool loadFromRenderedText(std::string texText, SDL_Color textColor);

    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr,
                SDL_RendererFlip flip = SDL_FLIP_NONE);

    int getWidth();
    int getHeight();

    SDL_Rect& getClip(unsigned int index);

private:
    void setClips();

    sdl2::TextureShPtr mTexture;

    //SDL_Color fontColor = {255, 255, 255};

    int width;
    int height;

    const int TILE_WIDTH = 16;
    const int TILE_HEIGHT = 16;

    std::vector<SDL_Rect> gTileClips;
};