/*
    Project Alpha
    Copyright (C) 2017  Pixima Development

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

#include <include/gfx/gfx.hpp>
#include <include/mapgen/mcore/mcore.hpp>

namespace MAPGEN {
    MCore mcore;
}

int MCore::init(std::string name, int width, int height) {
    if(!GFX::gfx->initGFX("../res/spritesheet.png", "MapGen")){
        return 1;
    }

    currentLocation = std::shared_ptr<MLocation>(new MLocation(name, width, height));

    gameLoop();

    return 0;
}

void MCore::gameLoop() {
    GFX::gfx->getWindow()->setActive();
    GFX::gfx->getWindow()->setKeyRepeatEnabled(false);

    while(GFX::gfx->getWindow()->isOpen()){
        sf::Event event;
        while(GFX::gfx->getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                GFX::gfx->getWindow()->close();
            }
            else if(event.type == sf::Event::KeyPressed){
                handleInput(event.key.code);
            }
        }
        draw();
    }
}

void MCore::handleInput(int key) {
    switch (key){
        case sf::Keyboard::Q: case sf::Keyboard::Escape:
            GFX::gfx->getWindow()->close();
            break;
        case sf::Keyboard::Up: case sf::Keyboard::W:
            moveCursor(0, (-1));
            break;
        case sf::Keyboard::Right: case sf::Keyboard::D:
            moveCursor(1, 0);
            break;
        case sf::Keyboard::Down: case sf::Keyboard::S:
            moveCursor(0, 1);
            break;
        case sf::Keyboard::Left: case sf::Keyboard::A:
            moveCursor((-1), 0);
            break;
        case sf::Keyboard::N:
            currentLocation->createArea();
            break;
        case sf::Keyboard::Num1: case sf::Keyboard::Numpad1:
            createTile(ENUMS::TTYPE::GRASS);
            break;
        case sf::Keyboard::Num2: case sf::Keyboard::Numpad2:
            createTile(ENUMS::TTYPE::MOUNTAIN);
            break;
        case sf::Keyboard::Num3 : case sf::Keyboard::Numpad3:
            createTile(ENUMS::TTYPE::SNOW);
            break;
        case sf::Keyboard::Num4 : case sf::Keyboard::Numpad4:
            createTile(ENUMS::TTYPE::WATER);
            break;
        default:
            break;
    }
}

void MCore::draw() {
    GFX::gfx->getWindow()->clear(sf::Color::Black);

    if(currentLocation != nullptr){
        currentLocation->drawChunk();
    }

    GFX::gfx->getWindow()->display();
}

void MCore::moveCursor(int xOffset, int yOffset) {
    if(currentLocation != nullptr){
        currentLocation->moveCursor(xOffset, yOffset);
    }
}

void MCore::setCurrentLocation(const std::shared_ptr<MLocation> location) {
    currentLocation = location;
}

const std::shared_ptr<MLocation> MCore::getCurrentLocation() {
    return currentLocation;
}

void MCore::createTile(ENUMS::TTYPE ttype) {
    if(currentLocation->getCurrentArea() != nullptr){
        currentLocation->getCurrentArea()->createTileAtCursor(ttype);
    }
}
