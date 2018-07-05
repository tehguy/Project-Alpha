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

#pragma once

#include <memory>
#include <vector>

#include "../core/constants.hpp"

class Graphics {
protected:
    Graphics() = default;

public:
    static std::shared_ptr<Graphics> Instance();

    bool checkWithCamera(const sf::Rect<int>& object) const;
    bool initGFX(const std::string &tileTexturePath, const std::string &windowName,
                 unsigned int screenWidth = CONSANTS::SCREEN_WIDTH,
                 unsigned int screenHeight = CONSANTS::SCREEN_HEIGHT, unsigned int framerate = 60);

    std::shared_ptr<sf::RenderWindow> getWindow();
    sf::Sprite createSprite(sf::Rect<int> &spriteRect) const;

    void centerCamera(const sf::Vector2i &prevPos, const sf::Vector2i &currentPos);
    void forceCenterCamera(const sf::Vector2i &posToCenterOn);

private:
    bool loadSpriteSheet(const std::string& filePath);
    bool checkCollision(const sf::Rect<int>& a, const sf::Rect<int>& b) const;

    void initCamera(int w, int h);
    void moveCamera(const sf::Vector2f &offset);

    std::shared_ptr<sf::RenderWindow> window;
    sf::View camera;
    sf::Texture tileTexture;

    sf::Rect<int> actualCameraBounds;

    static std::shared_ptr<Graphics> gfxInstance;
};