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

#include <cmath>

namespace GFX {
    std::shared_ptr<Graphics> gfx = std::shared_ptr<Graphics>(new Graphics());
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
    return checkCollision(actualCameraBounds, object);
}

bool Graphics::initGFX(std::string tileTexturePath, std::string windowName, unsigned int screenWidth,
                       unsigned int screenHeight, unsigned int framerate) {
    window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName));
    window->setFramerateLimit(framerate);

    camera.setSize(screenWidth, screenHeight);
    camera.setCenter(screenWidth/2, screenHeight/2);

    window->setView(camera);

    initCamera(screenWidth, screenHeight);

    return loadSpriteSheet(tileTexturePath);
}

bool Graphics::loadSpriteSheet(std::string filePath) {
    return tileTexture.loadFromFile(filePath);

}

const std::shared_ptr<sf::RenderWindow> &Graphics::getWindow() {
    return window;
}

const sf::Sprite Graphics::createSprite(sf::Rect<int> spriteRect) {
    sf::Sprite sprite;

    sprite.setTexture(tileTexture);
    sprite.setTextureRect(spriteRect);

    return sprite;
}

void Graphics::moveCamera(sf::Vector2f &offset) {
    actualCameraBounds.left += offset.x;
    actualCameraBounds.top += offset.y;

    sf::View view = window->getView();
    view.move(offset);
    window->setView(view);
}

void Graphics::centerCamera(sf::Vector2i prevPos, sf::Vector2i currentPos) {
    sf::View currentCam = window->getView();

    float adjustedCamCenterX = std::floor(currentCam.getCenter().x / CONSTANTS::TILE_WIDTH);
    float adjustedCamCenterY = std::floor(currentCam.getCenter().y / CONSTANTS::TILE_HEIGHT);


    sf::Vector2f offset;

    if(prevPos.x != currentPos.x){
        if(adjustedCamCenterX != currentPos.x){
            offset.x = ((currentPos.x - adjustedCamCenterX) * CONSTANTS::TILE_WIDTH);
        }
    }

    if(prevPos.y != currentPos.y){
        if(adjustedCamCenterY != currentPos.y){
            offset.y = ((currentPos.y - adjustedCamCenterY) * CONSTANTS::TILE_HEIGHT);
        }
    }

    moveCamera(offset);
}

void Graphics::forceCenterCamera(sf::Vector2i posToCenterOn) {
    sf::View currentCam = window->getView();

    float adjustedCamCenterX = std::floor(currentCam.getCenter().x / CONSTANTS::TILE_WIDTH);
    float adjustedCamCenterY = std::floor(currentCam.getCenter().y / CONSTANTS::TILE_HEIGHT);

    sf::Vector2f offset;

    if(adjustedCamCenterX != posToCenterOn.x){
        offset.x = ((posToCenterOn.x - adjustedCamCenterX) * CONSTANTS::TILE_WIDTH);
    }

    if(adjustedCamCenterY != posToCenterOn.y){
        offset.y = ((posToCenterOn.y - adjustedCamCenterY) * CONSTANTS::TILE_HEIGHT);
    }

    moveCamera(offset);
}

void Graphics::initCamera(int w, int h) {
    actualCameraBounds.left = 0;
    actualCameraBounds.top = 0;
    actualCameraBounds.width = w;
    actualCameraBounds.height = h;
}
