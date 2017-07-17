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

namespace MAIN {
    Core core;
}

Core::Core() {

}

Core::~Core() {

}

void Core::init() {
    if(!GFX::gfx.initGFX()){
        return;
    }

    currentArea = std::shared_ptr<Area>(new Area("test", 80, 50));
    currentArea->genRandom(237);

    gameLoop();
}

void Core::close() {

}

void Core::gameLoop() {
    while(GFX::gfx.getWindow()->isOpen()){
        sf::Event event;
        while(GFX::gfx.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                GFX::gfx.getWindow()->close();
            }
        }

        GFX::gfx.getWindow()->setActive();
        GFX::gfx.getWindow()->clear(sf::Color::Black);

        //OGL drawing commands
        currentArea->draw();

        GFX::gfx.getWindow()->display();
    }
}

const std::shared_ptr<Player> &Core::getPlayer() {
    return player;
}

const std::shared_ptr<Location> &Core::getCurrentLocation() {
    return currentLocation;
}

const std::shared_ptr<Area> &Core::getCurrentArea() {
    return currentArea;
}

bool Core::movePlayer(unsigned int x, unsigned int y) {
    return currentArea->moveEntity(x, y, *player);
}