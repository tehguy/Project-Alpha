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

#include <cmath>
#include <memory>
#include "gfx.hpp"

std::shared_ptr<Graphics> Graphics::gfxInstance = std::shared_ptr<Graphics>(nullptr);

std::shared_ptr<Graphics> Graphics::Instance() {
    if (gfxInstance == nullptr) {
        gfxInstance = std::shared_ptr<Graphics>(new Graphics());
    }

    return gfxInstance;
}

bool Graphics::checkWithCamera(const sf::Rect<int> &object) const {
    return checkCollision(actualCameraBounds, object);
}

bool Graphics::checkCollision(const sf::Rect<int> &a, const sf::Rect<int> &b) const {
    const int leftA = a.left;
    const int leftB = b.left;
    const int rightA = a.left + a.width;
    const int rightB = b.left + b.width;
    const int topA = a.top;
    const int topB = b.top;
    const int bottomA = a.top + a.height;
    const int bottomB = b.top + b.height;

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;

    return leftA < rightB;
}

bool Graphics::initGFX(const std::string &tileTexturePath, const std::string &windowName, unsigned int screenWidth,
                       unsigned int screenHeight, unsigned int framerate) {
    sf::RenderWindow temp(sf::VideoMode(screenWidth, screenHeight), windowName);

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), windowName);
    window->setFramerateLimit(framerate);

    camera.setSize(screenWidth, screenHeight);
    camera.setCenter(screenWidth/2, screenHeight/2);

    window->setView(camera);

    initCamera(screenWidth, screenHeight);

    return loadSpriteSheet(tileTexturePath);
}

void Graphics::initCamera(const int w, const int h) {
    actualCameraBounds.left = 0;
    actualCameraBounds.top = 0;
    actualCameraBounds.width = w;
    actualCameraBounds.height = h;
}

bool Graphics::loadSpriteSheet(const std::string &filePath) {
    return tileTexture.loadFromFile(filePath);
}

std::shared_ptr<sf::RenderWindow> Graphics::getWindow() {
    return window;
}

sf::Sprite Graphics::createSprite(sf::Rect<int> &spriteRect) const{
    sf::Sprite sprite;

    sprite.setTexture(tileTexture);
    sprite.setTextureRect(spriteRect);

    return sprite;
}

void Graphics::centerCamera(const sf::Vector2i &prevPos, const sf::Vector2i &currentPos) {
    sf::View currentCam = window->getView();

    float adjustedCamCenterX = std::floor(currentCam.getCenter().x / CONSANTS::TILE_WIDTH);
    float adjustedCamCenterY = std::floor(currentCam.getCenter().y / CONSANTS::TILE_HEIGHT);

    sf::Vector2f offset;

    if (prevPos.x != currentPos.x) {
        if (adjustedCamCenterX != currentPos.x) {
            offset.x = ((currentPos.x - adjustedCamCenterX) * CONSANTS::TILE_WIDTH);
        }
    }

    if (prevPos.y != currentPos.y) {
        if (adjustedCamCenterY != currentPos.y) {
            offset.y = ((currentPos.y - adjustedCamCenterY) * CONSANTS::TILE_HEIGHT);
        }
    }

    moveCamera(offset);
}

void Graphics::moveCamera(const sf::Vector2f &offset) {
    actualCameraBounds.left += offset.x;
    actualCameraBounds.top += offset.y;

    sf::View view = window->getView();
    view.move(offset);
    window->setView(view);
}

void Graphics::forceCenterCamera(const sf::Vector2i &posToCenterOn) {
    sf::View currentCam = window->getView();

    float adjustedCamCenterX = std::floor(currentCam.getCenter().x / CONSANTS::TILE_WIDTH);
    float adjustedCamCenterY = std::floor(currentCam.getCenter().y / CONSANTS::TILE_HEIGHT);

    sf::Vector2f offset;

    if (adjustedCamCenterX != posToCenterOn.x) {
        offset.x = ((posToCenterOn.x - adjustedCamCenterX) * CONSANTS::TILE_WIDTH);
    }

    if (adjustedCamCenterY != posToCenterOn.y) {
        offset.y = ((posToCenterOn.y - adjustedCamCenterY) * CONSANTS::TILE_HEIGHT);
    }

    moveCamera(offset);
}
