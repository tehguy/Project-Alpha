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
#include <include/core/constants.hpp>
#include <include/mapgen/mgfx/mgfx.hpp>

namespace MGFX {
    std::shared_ptr<MGraphics> mgfx = std::shared_ptr<MGraphics>(new MGraphics);
}

MGraphics::MGraphics() {

}

bool MGraphics::initGFX() {
    std::shared_ptr<sf::RenderWindow> window;
    window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(CONSTANTS::SCREEN_WIDTH,
                                                                                 CONSTANTS::SCREEN_HEIGHT),
                                                                   "MapGen"));
    window->setFramerateLimit(60);

    sf::View camera;
    camera.setSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    camera.setCenter(CONSTANTS::SCREEN_WIDTH/2, CONSTANTS::SCREEN_HEIGHT/2);

    window->setView(camera);

    setWindow(window);
    initCamera(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);

    return loadSpriteSheet("../res/spritesheet.png");
}