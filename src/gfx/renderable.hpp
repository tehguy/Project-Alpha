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

#include "../core/constants.hpp"

class Renderable {
public:
    Renderable(unsigned int x, unsigned int y, sf::Rect<int> spriteRect);
    Renderable(unsigned int x, unsigned int y, int tileID);

    void queueRender() const;
    void setRenderPosition(unsigned int x, unsigned int y);

private:
    void generateQuadCoords(unsigned int x, unsigned int y);
    void generateTexCoords(unsigned int tileID);

    sf::Rect<int> renderBox;
    sf::Sprite worldSprite;

    std::vector<sf::Vertex> quad;
};
