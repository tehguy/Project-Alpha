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

#include <SDL2/SDL.h>
#include <memory>

namespace sdl2 {
    struct SDL_Deleter {
        void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
        void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
        void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
        void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
        void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
    };

    template<class T, class D = std::default_delete<T>>
    struct shared_ptr_with_deleter : public std::shared_ptr<T> {
        explicit shared_ptr_with_deleter(T* t = nullptr) : std::shared_ptr<T>(t, D()) {}

        void reset(T* t = nullptr){
            std::shared_ptr<T>::reset(t, D());
        }
    };

    using SurfaceShPtr  = shared_ptr_with_deleter<SDL_Surface,  SDL_Deleter>;
    using TextureShPtr  = shared_ptr_with_deleter<SDL_Texture,  SDL_Deleter>;
    using RendererShPtr = shared_ptr_with_deleter<SDL_Renderer, SDL_Deleter>;
    using WindowShPtr   = shared_ptr_with_deleter<SDL_Window,   SDL_Deleter>;
    using RWopsShPtr    = shared_ptr_with_deleter<SDL_RWops,    SDL_Deleter>;
}