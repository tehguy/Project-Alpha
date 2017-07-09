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

#include <include/core/tiletexture.hpp>
#include <include/entity/player.hpp>
#include <include/world/location.hpp>

class Core {
public:
    Core();
    ~Core();

    void init();
    void close();

    const std::shared_ptr<Player>& getPlayer();
    const std::shared_ptr<Area>& getCurrentArea();
    const sdl2::RendererShPtr& getRenderer();

    SDL_Rect& getCamera();
    TileTexture& getTileTexture();

    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool loadMedia();

    //TTF_Font* getFont();

private:
    void gameLoop();
    bool initSDL();

    sdl2::WindowShPtr screen;
    sdl2::RendererShPtr gRender;

    std::shared_ptr<Player> player;

    std::shared_ptr<Area> currentArea;

    SDL_Rect camera;
    TileTexture gTileTexture;
    //TTF_Font* font;

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
};

namespace MAIN {
    extern Core core;
    const int TEXT_SIZE = 14;
}