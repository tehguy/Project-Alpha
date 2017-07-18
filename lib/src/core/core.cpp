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
#include <include/gfx/gfx.hpp>

namespace MAIN {
    Core core;
}

void Core::init() {
    if(!GFX::gfx.initGFX()){
        return;
    }

    player = std::shared_ptr<Player>(new Player(5, 5, 20));

    currentLocation = std::shared_ptr<Location>(new Location("Big Test", 2, 1));
    Area area1("Test1", 10, 10);
    Area area2("Test2", 20, 22);

    area1.genRandom(288);
    area1.setEntitySymbol(5, 5, &(*player));
    area2.genRandom(156);

    currentLocation->placeArea(0, 0, area1);
    currentLocation->placeArea(1, 0, area2);
    currentLocation->setCurrentArea(0, 0);

    gameLoop();
}

void Core::gameLoop() {
    GFX::gfx.getWindow()->setActive();
    while(GFX::gfx.getWindow()->isOpen()){
        sf::Event event;
        while(GFX::gfx.getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                GFX::gfx.getWindow()->close();
            }
            else if(event.type == sf::Event::KeyPressed){
                handleInput(event.key.code);
            }
        }
        GFX::gfx.getWindow()->clear(sf::Color::Black);

        currentLocation->getCurrentArea()->draw();

        GFX::gfx.getWindow()->display();
    }
}

bool Core::movePlayer(int xOffset, int yOffset) {
    return currentLocation->getCurrentArea()->movePlayer(xOffset, yOffset, *player);
}

void Core::handleInput(int key) {
    bool playerMoved = false;
    switch (key){
        case sf::Keyboard::Q: case sf::Keyboard::Escape:
            GFX::gfx.getWindow()->close();
            break;
        case sf::Keyboard::Up: case sf::Keyboard::W:
            playerMoved = movePlayer(0, (-1));
            break;
        case sf::Keyboard::Right: case sf::Keyboard::D:
            playerMoved = movePlayer(1, 0);
            break;
        case sf::Keyboard::Down: case sf::Keyboard::S:
            playerMoved = movePlayer(0, 1);
            break;
        case sf::Keyboard::Left: case sf::Keyboard::A:
            playerMoved = movePlayer((-1), 0);
            break;
        default:
            break;
    }
    centerCameraAroundPlayer(playerMoved);
}

void Core::centerCameraAroundPlayer(bool playerMoved) {
    if(playerMoved){
        sf::Vector2i playerPrevPos = player->getPreviousPosition();
        sf::Vector2i playerCurPos = player->getWorldPosition();
        sf::Vector2i areaDim = currentLocation->getCurrentArea()->getDimensions();
        GFX::gfx.centerCamera(playerPrevPos, playerCurPos, areaDim);
    }
}
