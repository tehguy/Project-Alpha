/*
    Project Alpha
    Copyright (C) 2017  tehguy

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

#include "core.hpp"

#include "../gfx/gfx.hpp"

int Core::init() {
    if (!Graphics::Instance().initGFX("./res/spritesheet.png", "Project Alpha")) return 1;

    genTestArea();

    gameLoop();

    return 0;
}

void Core::gameLoop() {
    Graphics::Instance().setActive();
    while (Graphics::Instance().windowIsOpen()) {
        sf::Event event{};
        while (Graphics::Instance().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Graphics::Instance().shutdown();
            }
            else if (event.type == sf::Event::KeyPressed) {
                handleInput(event.key.code);
            }
        }

        drawGame();
    }
}

void Core::handleInput(int key) {
    switch (key) {
        case sf::Keyboard::Escape:
            Graphics::Instance().shutdown();
            break;
        default:
            break;
    }
}

void Core::genTestArea() {
    currentLocation = std::make_unique<Location>("Big Test", 2, 2);
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

    currentLocation->setCurrentArea(0, 0);
}

void Core::drawGame() {
    Graphics::Instance().clearWindow();

    if (currentLocation != nullptr) {
        currentLocation->drawChunk();
    }
    Graphics::Instance().draw();
    Graphics::Instance().display();
}
