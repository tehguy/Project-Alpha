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

#include <include/core/core.hpp>

ENGINE_API Core::Core() {

}

ENGINE_API int Core::init() {
    if(!Graphics::Instance()->initGFX("./res/spritesheet.png", "Project Alpha")){
        return 1;
    }

    genTestArea();

    gameLoop();

    return 0;
}

void Core::gameLoop() {
    Graphics::Instance()->getWindow()->setActive();
    while(Graphics::Instance()->getWindow()->isOpen()){
        sf::Event event;
        while(Graphics::Instance()->getWindow()->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                Graphics::Instance()->getWindow()->close();
            }
            else if(event.type == sf::Event::KeyPressed){
                handleInput(event.key.code);
            }
        }
        draw();
    }
}

void Core::movePlayer(int xOffset, int yOffset) {
    if(currentLocation != nullptr){
        currentLocation->movePlayer(xOffset, yOffset);
    }
}

void Core::handleInput(int key) {
    switch (key){
        case sf::Keyboard::Q: case sf::Keyboard::Escape:
            Graphics::Instance()->getWindow()->close();
            break;
        case sf::Keyboard::Up: case sf::Keyboard::W:
            movePlayer(0, (-1));
            break;
        case sf::Keyboard::Right: case sf::Keyboard::D:
            movePlayer(1, 0);
            break;
        case sf::Keyboard::Down: case sf::Keyboard::S:
            movePlayer(0, 1);
            break;
        case sf::Keyboard::Left: case sf::Keyboard::A:
            movePlayer((-1), 0);
            break;
        default:
            break;
    }
}

void Core::genTestArea() {
    currentLocation = std::shared_ptr<Location>(new Location("Big Test", 2, 2));
    Area area1("Test1");
    Area area2("Test2");
    Area area3("Test3");
    Area area4("Test4");

    area1.genRandom(288);
    area2.genRandom(243);
    area3.genRandom(146);
    area4.genRandom(723);

    currentLocation->placeArea(0, 0, area1);
    currentLocation->placeArea(1, 0, area2);
    currentLocation->placeArea(0, 1, area3);
    currentLocation->placeArea(1, 1, area4);
    currentLocation->setCurrentArea(1, 1);
    currentLocation->getCurrentArea()->spawnPlayer(0, 0, 20);

    Graphics::Instance()->forceCenterCamera(currentLocation->getCurrentArea()->passPlayer().getWorldPosition());
}

void Core::draw() {
    Graphics::Instance()->getWindow()->clear(sf::Color::Black);

    if(currentLocation != nullptr){
        currentLocation->drawChunk();
    }

    Graphics::Instance()->getWindow()->display();
}

void Core::setCurrentLocation(const std::shared_ptr<Location> location) {
    currentLocation = location;
}

const std::shared_ptr<Location> Core::getCurrentLocation() {
    return currentLocation;
}
