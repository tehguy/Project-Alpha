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

#include <include/gfx/gfx.hpp>
#include <include/mapgen/mworld/marea.hpp>

MArea::MArea(std::string name) : Area(name) {
    cursor = std::shared_ptr<Cursor>(nullptr);

    for(unsigned int i = 0; i < getDimensions().x; i++){
        cursorMap.push_back(std::vector<std::shared_ptr<Cursor>>());
        cursorMap.at(i).reserve((unsigned long) getDimensions().y);

        for(unsigned int j = 0; j < getDimensions().y; j++){
            cursorMap.at(i).push_back(std::shared_ptr<Cursor>(nullptr));
        }
    }
}

void MArea::spawnCursor(int x, int y) {
    if(cursor == nullptr){
        cursor = std::shared_ptr<Cursor>(new Cursor());
        moveCursor(x, y);
    }
    else{
        moveCursor(x, y);
    }
}

bool MArea::moveCursor(int xOffset, int yOffset) {
    int xTarget = cursor->getWorldPosition().x + xOffset;
    int yTarget = cursor->getWorldPosition().y + yOffset;

    if((xTarget >= 0 && xTarget < getDimensions().x) && (yTarget >= 0 && yTarget < getDimensions().y)){
        int prevXPos = cursor->getWorldPosition().x;
        int prevYPos = cursor->getWorldPosition().y;

        cursor->setPrevPos(prevXPos, prevYPos);
        setCursorMap(prevXPos, prevYPos, std::shared_ptr<Cursor>(nullptr));

        cursor->setWorldPosition(xTarget, yTarget);
        setCursorMap(xTarget, yTarget, cursor);

        GFX::gfx->centerCamera(cursor->getPreviousPosition(), cursor->getWorldPosition());
        return true;
    }

    return false;
}

void MArea::setCursorMap(int x, int y, const std::shared_ptr<Cursor> set) {
    cursorMap.at(static_cast<unsigned long>(x)).at(static_cast<unsigned long>(y)) = set;
}

bool MArea::moveCursorToThisArea(int xOffset, int yOffset, const std::shared_ptr<MArea> &prevArea) {
    cursor = std::make_shared<Cursor>(prevArea->passCursor());

    sf::Vector2i prevPos = cursor->getWorldPosition();

    cursor->setWorldPosition(0, 0);

    if(moveCursor(xOffset, yOffset)){
        prevArea->despawnCursor();
        return true;
    }

    cursor->setWorldPosition(prevPos.x, prevPos.y);
    cursor = std::shared_ptr<Cursor>(nullptr);
    return false;
}

void MArea::despawnCursor() {
    setCursorMap(cursor->getWorldPosition().x, cursor->getWorldPosition().y, std::shared_ptr<Cursor>(nullptr));

    cursor = nullptr;
}

Cursor MArea::passCursor() {
    return *cursor;
}

void MArea::draw() {
    if(cursor != nullptr){
        cursor->render();
    }

    Area::draw();
}
