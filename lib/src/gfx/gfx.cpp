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
#include <include/gfx/gfx.hpp>

namespace GFX {
    Graphics gfx;
}

Graphics::Graphics() {

}

bool Graphics::checkCollision(sf::Rect<int> a, sf::Rect<int> b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.left;
    rightA = a.left + a.width;
    topA = a.top;
    bottomA = a.top + a.height;

    //Calculate the sides of rect B
    leftB = b.left;
    rightB = b.left + b.width;
    topB = b.top;
    bottomB = b.top + b.height;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    return leftA < rightB;

}

bool Graphics::checkWithinCamera(sf::Rect<int> object) {
    int left = (int) camera->getViewport().left;
    int top = (int) camera->getViewport().top;
    int width = (int) camera->getViewport().width;
    int height = (int) camera->getViewport().height;

    sf::Rect<int> cameraRect(left, top, width, height);

    return checkCollision(cameraRect, object);
}

bool Graphics::initGFX() {
    window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(CONSTANTS::SCREEN_WIDTH,
                                                                      CONSTANTS::SCREEN_HEIGHT), "Window"));
    window->setFramerateLimit(60);

    camera = std::shared_ptr<sf::View>(new sf::View());
    camera->setSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    camera->setCenter(CONSTANTS::SCREEN_WIDTH/2, CONSTANTS::SCREEN_HEIGHT/2);

    window->setView(*camera);

    setClips();

    return loadSpriteSheet();
}

bool Graphics::loadSpriteSheet() {
    sf::Image image;

    if(!image.loadFromFile("./lib/spritesheet.png")){
        return false;
    }

    textureRects.push_back(sf::Rect<int>(0, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(16, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(32, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(48, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(0, 16, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));

    return tileTexture.loadFromImage(image);
}

void Graphics::setClips() {

}

const std::shared_ptr<sf::RenderWindow> &Graphics::getWindow() {
    return window;
}

const std::shared_ptr<sf::View> &Graphics::getPlayerCamera() {
    return camera;
}

const sf::Sprite Graphics::createSprite(unsigned int clipIndex) {
    sf::Sprite sprite;

    sprite.setTexture(tileTexture);
    sprite.setTextureRect(textureRects.at(clipIndex));

    return sprite;
}
