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

TileTexture::TileTexture() {
    mTexture = sdl2::TextureShPtr(nullptr);

    width = 0;
    height = 0;
}

TileTexture::~TileTexture() {
    free();
}

bool TileTexture::loadFromRenderedText(std::string texText, SDL_Color textColor) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(MAIN::core.getFont(), texText.c_str(), textColor);
    if(textSurface != nullptr){
        mTexture = sdl2::TextureShPtr(SDL_CreateTextureFromSurface(MAIN::core.getRenderer().get(), textSurface));

        if(mTexture != nullptr){
            width = textSurface->w;
            height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != nullptr;
}

void TileTexture::free() {
    if(mTexture != nullptr){
        SDL_DestroyTexture(mTexture.get());
        mTexture = sdl2::TextureShPtr(nullptr);
        width = 0;
        height = 0;
    }
}

void TileTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture.get(), red, green, blue);
}

void TileTexture::setBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(mTexture.get(), blendMode);
}

void TileTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture.get(), alpha);
}

void TileTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, width, height};

    if(clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(MAIN::core.getRenderer().get(), mTexture.get(), clip, &renderQuad, angle, center, flip);
}

int TileTexture::getWidth() {
    return width;
}

int TileTexture::getHeight() {
    return height;
}
