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
#include <cmath>

namespace MAIN {
    Core core;
}

void Core::init() {
    if(!GFX::gfx.initGFX()){
        return;
    }

    player = std::shared_ptr<Player>(new Player(25, 22, 20));

    currentArea = std::shared_ptr<Area>(new Area("test", 90, 60));
    currentArea->genRandom(237);
    currentArea->setEntitySymbol(player->getWorldXPos(), player->getWorldYPos(), &(*player));
    centerCameraAroundPlayer(true);

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

        currentArea->draw();

        GFX::gfx.getWindow()->display();
    }
}

bool Core::movePlayer(unsigned int x, unsigned int y) {
    return currentArea->moveEntity(x, y, *player);
}

void Core::handleInput(int key) {
    bool didMove = false;
    switch (key){
        case sf::Keyboard::Q: case sf::Keyboard::Escape:
            GFX::gfx.getWindow()->close();
            break;
        case sf::Keyboard::Up: case sf::Keyboard::W:
            didMove = movePlayer(player->getWorldXPos(), player->getWorldYPos() - 1);
            break;
        case sf::Keyboard::Right: case sf::Keyboard::D:
            didMove = movePlayer(player->getWorldXPos() + 1, player->getWorldYPos());
            break;
        case sf::Keyboard::Down: case sf::Keyboard::S:
            didMove = movePlayer(player->getWorldXPos(), player->getWorldYPos() + 1);
            break;
        case sf::Keyboard::Left: case sf::Keyboard::A:
            didMove = movePlayer(player->getWorldXPos() - 1, player->getWorldYPos());
            break;
        default:
            break;
    }
    centerCameraAroundPlayer(didMove);
}

void Core::centerCameraAroundPlayer(bool didPlayerMove) {
    if(didPlayerMove){
        sf::View camera = GFX::gfx.getWindow()->getView();
        sf::Rect<int> cameraPort = GFX::gfx.getWindow()->getViewport(GFX::gfx.getWindow()->getView());

        float adjustedCamCenterX = std::floor(camera.getCenter().x / CONSTANTS::TILE_WIDTH);
        float adjustedCamCenterY = std::floor(camera.getCenter().y / CONSTANTS::TILE_HEIGHT);

        float xBufferInTiles = ((CONSTANTS::SCREEN_WIDTH / 2) / CONSTANTS::TILE_WIDTH);
        float yBufferInTiles = ((CONSTANTS::SCREEN_HEIGHT / 2) / CONSTANTS::TILE_HEIGHT);


        sf::Vector2f offset;

        if(player->getPrevX() != player->getWorldXPos()){
            if(adjustedCamCenterX != player->getWorldXPos()){
                offset.x = ((player->getWorldXPos() - adjustedCamCenterX) * CONSTANTS::TILE_WIDTH);
            }
            if((adjustedCamCenterX + (offset.x / CONSTANTS::TILE_WIDTH)) < xBufferInTiles){
                offset.x = 0;
            }
            if((currentArea->getWidth() - xBufferInTiles) < (adjustedCamCenterX + (offset.x / CONSTANTS::TILE_WIDTH))){
                offset.x = 0;
            }
        }

        if(player->getPrevY() != player->getWorldYPos()){
            if(adjustedCamCenterY != player->getWorldYPos()){
                offset.y = ((player->getWorldYPos() - adjustedCamCenterY) * CONSTANTS::TILE_HEIGHT);
            }
            if((adjustedCamCenterY + (offset.y / CONSTANTS::TILE_HEIGHT)) < yBufferInTiles){
                offset.y = 0;
            }
            if((currentArea->getHeight() - yBufferInTiles) < (adjustedCamCenterY + 1 + (offset.y / CONSTANTS::TILE_HEIGHT))){
                offset.y = 0;
            }
        }
        GFX::gfx.moveCamera(offset);
    }
}
