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

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>

class Graphics {
public:
    Graphics();

    bool checkWithinCamera(sf::Rect<int> object);

    bool initGFX();
    bool loadSpriteSheet();

    const std::shared_ptr<sf::RenderWindow>& getWindow();
    const sf::Sprite createSprite(sf::Rect<int> spriteRect);

    void centerCamera(sf::Vector2i playerPrevPos, sf::Vector2i playerCurrentPos);
    void forceCenterCamera(sf::Vector2i playerCurrentPos);

private:
    bool checkCollision(sf::Rect<int> a, sf::Rect<int> b);
    void moveCamera(sf::Vector2f& offset);

    std::shared_ptr<sf::RenderWindow> window;
    sf::View camera;
    sf::Texture tileTexture;

    sf::Rect<int> actualCameraBounds;
};

namespace GFX {
    extern Graphics gfx;
}