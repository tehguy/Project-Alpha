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
    return checkCollision(actualCameraBounds, object);
}

bool Graphics::initGFX() {
    window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(CONSTANTS::SCREEN_WIDTH,
                                                                      CONSTANTS::SCREEN_HEIGHT), "CPPAdventures"));
    window->setFramerateLimit(60);

    camera.setSize(CONSTANTS::SCREEN_WIDTH, CONSTANTS::SCREEN_HEIGHT);
    camera.setCenter(CONSTANTS::SCREEN_WIDTH/2, CONSTANTS::SCREEN_HEIGHT/2);

    window->setView(camera);

    actualCameraBounds.left = 0;
    actualCameraBounds.top = 0;
    actualCameraBounds.width = CONSTANTS::SCREEN_WIDTH;
    actualCameraBounds.height = CONSTANTS::SCREEN_HEIGHT;

    return loadSpriteSheet();
}

bool Graphics::loadSpriteSheet() {
    if(!tileTexture.loadFromFile("./lib/spritesheet.png")){
        return false;
    }

    textureRects.push_back(sf::Rect<int>(0, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(16, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(32, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(48, 0, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));
    textureRects.push_back(sf::Rect<int>(0, 16, CONSTANTS::TILE_WIDTH, CONSTANTS::TILE_HEIGHT));

    return true;
}

const std::shared_ptr<sf::RenderWindow> &Graphics::getWindow() {
    return window;
}

const sf::Sprite Graphics::createSprite(unsigned int clipIndex) {
    sf::Sprite sprite;

    sprite.setTexture(tileTexture);
    sprite.setTextureRect(textureRects.at(clipIndex));

    return sprite;
}

void Graphics::moveCamera(sf::Vector2f &offset) {
    actualCameraBounds.left += offset.x;
    actualCameraBounds.top += offset.y;

    sf::View view = window->getView();
    view.move(offset);
    window->setView(view);
}

void Graphics::centerCamera(sf::Vector2i playerPrevPos, sf::Vector2i playerCurrentPos, sf::Vector2i areaDimensions) {
    sf::View currentCam = window->getView();

    float adjustedCamCenterX = std::floor(currentCam.getCenter().x / CONSTANTS::TILE_WIDTH);
    float adjustedCamCenterY = std::floor(currentCam.getCenter().y / CONSTANTS::TILE_HEIGHT);

    float xBufferInTiles = ((CONSTANTS::SCREEN_WIDTH / 2) / CONSTANTS::TILE_WIDTH);
    float yBufferInTiles = ((CONSTANTS::SCREEN_HEIGHT / 2) / CONSTANTS::TILE_HEIGHT);


    sf::Vector2f offset;

    if(playerPrevPos.x != playerCurrentPos.x){
        if(adjustedCamCenterX != playerCurrentPos.x){
            offset.x = ((playerCurrentPos.x - adjustedCamCenterX) * CONSTANTS::TILE_WIDTH);
        }
        if((adjustedCamCenterX + (offset.x / CONSTANTS::TILE_WIDTH)) < xBufferInTiles){
            offset.x = 0;
        }
        if((areaDimensions.x - xBufferInTiles) < (adjustedCamCenterX + (offset.x / CONSTANTS::TILE_WIDTH))){
            offset.x = 0;
        }
    }

    if(playerPrevPos.y != playerCurrentPos.y){
        if(adjustedCamCenterY != playerCurrentPos.y){
            offset.y = ((playerCurrentPos.y - adjustedCamCenterY) * CONSTANTS::TILE_HEIGHT);
        }
        if((adjustedCamCenterY + (offset.y / CONSTANTS::TILE_HEIGHT)) < yBufferInTiles){
            offset.y = 0;
        }
        if((areaDimensions.y - yBufferInTiles) < (adjustedCamCenterY + 1 + (offset.y / CONSTANTS::TILE_HEIGHT))){
            offset.y = 0;
        }
    }

    moveCamera(offset);
}
