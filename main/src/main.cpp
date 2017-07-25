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

void gameLoop();

int main() {

    if(!GFX::gfx.initGFX()){
        return 1;
    }

    MAIN::core.init();

    gameLoop();

	return 0;
}

void gameLoop() {
    GFX::gfx.getWindow()->setActive();
    while(GFX::gfx.getWindow()->isOpen()){
        sf::Event event;
        while(GFX::gfx.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                GFX::gfx.getWindow()->close();
            }
            else if(event.type == sf::Event::KeyPressed){
                MAIN::core.handleInput(event.key.code);
            }
        }
        MAIN::core.draw();
    }
}