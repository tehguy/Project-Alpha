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

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

#include <include/core/constants.hpp>

class Graphics {
protected:
    Graphics();

public:
    static std::shared_ptr<Graphics> Instance();
    bool checkWithinCamera(sf::Rect<int> object);

    bool initGFX(std::string tileTexturePath, std::string windowName, unsigned int screenWidth = CONSTANTS::SCREEN_WIDTH,
                             unsigned int screenHeight = CONSTANTS::SCREEN_HEIGHT, unsigned int framerate = 60);

    const std::shared_ptr<sf::RenderWindow>& getWindow();
    const sf::Sprite createSprite(sf::Rect<int> spriteRect);

    void centerCamera(sf::Vector2i prevPos, sf::Vector2i currentPos);
    void forceCenterCamera(sf::Vector2i posToCenterOn);

private:
    bool loadSpriteSheet(std::string filePath);

    void initCamera(int w, int h);
    bool checkCollision(sf::Rect<int> a, sf::Rect<int> b);
    void moveCamera(sf::Vector2f& offset);

    std::shared_ptr<sf::RenderWindow> window;
    sf::View camera;
    sf::Texture tileTexture;

    sf::Rect<int> actualCameraBounds;

    static std::shared_ptr<Graphics> gfxInstance;
};