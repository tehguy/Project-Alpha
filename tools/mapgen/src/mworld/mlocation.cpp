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

#include <include/gfx/gfx.hpp>

#include <include/mapgen/mworld/marea.hpp>
#include <include/mapgen/mworld/mlocation.hpp>

#include <iostream>

MLocation::MLocation(std::string name, int width, int height) {
    heldLocation = std::shared_ptr<Location>(new Location(name, width, height));
}

sf::Vector2i MLocation::getDimensions() {
    return dimensions;
}

void MLocation::createArea() {
    std::string name;
    int x = 0, y = 0;

    std::cout << std::endl;
    std::cout << "Enter area name: ";
    std::getline(std::cin, name);
    std::cin.clear();

    do{
        std::cout << "Enter area x/y: ";
        std::cin >> x >> y;

        if((x < 0 || x >= dimensions.x) || (y < 0 || y >= dimensions.y)){
            std::cout << std::endl << "Incorrect location specified" << std::endl;
        }
    } while ((x < 0 || x >= dimensions.x) || (y < 0 || y >= dimensions.y));

    MArea mArea(name);

    placeArea(x, y, mArea);
    setCurrentArea(x, y);
    getCurrentMArea()->spawnCursor(0, 0);
}

void MLocation::placeArea(int x, int y, MArea area) {
    if((x >= 0) && (x < getDimensions().x) && (y >= 0) && (y < getDimensions().y)){
        area.getHeldArea()->setLocationalPosition(sf::Vector2i(x, y));
        areas.at((unsigned long) x).at((unsigned long) y) = std::make_shared<MArea>(area);
    }
}

const std::shared_ptr<MArea> &MLocation::getArea(int x, int y) {
    return areas.at((unsigned long) x).at((unsigned long) y);
}

std::string MLocation::getName() {
    return locationName;
}

void MLocation::setCurrentArea(int x, int y) {
    if(getArea((unsigned int) x, (unsigned int) y) != nullptr){
        std::shared_ptr<MArea> currentArea = getArea((unsigned int) x, (unsigned int) y);
        currentArea->getHeldArea()->resetRenderPos(0, 0);
        chunk.at(1).at(1) = currentArea;
        loadAdjacentMAreas();
    }
}

const std::shared_ptr<MArea> &MLocation::getCurrentMArea() {
    return chunk.at(1).at(1);
}

void MLocation::drawChunk() {
    for(auto& innerVec : chunk){
        for(auto& area : innerVec){
            if(area != nullptr){
                area->draw();
            }
        }
    }
}

void MLocation::moveCursor(int xOffset, int yOffset) {
    std::shared_ptr<Cursor> cursor = std::make_shared<Cursor>(getCurrentMArea()->passCursor());
    int xTarget = cursor->getWorldPosition().x + xOffset;
    int yTarget = cursor->getWorldPosition().y + yOffset;

    if(xTarget < 0){
        if(chunk.at(0).at(1) != nullptr){
            if(chunk.at(0).at(1)->moveCursorToThisArea((chunk.at(0).at(1)->getDimensions().x - 1),
                                                       cursor->getWorldPosition().y, getCurrentMArea())){
                moveToMArea((-1), 0);
            }
            return;
        }
    }
    else if(xTarget > (getCurrentMArea()->getDimensions().x - 1)){
        if(chunk.at(2).at(1) != nullptr){
            if(chunk.at(2).at(1)->moveCursorToThisArea(0, cursor->getWorldPosition().y, getCurrentMArea())){
                moveToMArea(1, 0);
            }
            return;
        }
    }


    if(yTarget < 0){
        if(chunk.at(1).at(0) != nullptr){
            if(chunk.at(1).at(0)->moveCursorToThisArea(cursor->getWorldPosition().x,
                                                       (chunk.at(1).at(0)->getDimensions().y - 1), getCurrentMArea())){
                moveToMArea(0, (-1));
            }
            return;
        }
    }
    else if(yTarget > (getCurrentMArea()->getDimensions().y - 1)){
        if(chunk.at(1).at(2) != nullptr){
            if(chunk.at(1).at(2)->moveCursorToThisArea(cursor->getWorldPosition().x, 0, getCurrentMArea())){
                moveToMArea(0, 1);
            }
            return;
        }
    }

    getCurrentMArea()->moveCursor(xOffset, yOffset);
}

void MLocation::moveToMArea(int xOffset, int yOffset) {
    int xTarget = getCurrentMArea()->getHeldArea()->getLocationalPosition().x + xOffset;
    int yTarget = getCurrentMArea()->getHeldArea()->getLocationalPosition().y + yOffset;

    if((xTarget >= 0) && (xTarget < getDimensions().x) && (yTarget >= 0) && (yTarget < getDimensions().y)){
        setCurrentArea(xTarget, yTarget);
        GFX::gfx->forceCenterCamera(getCurrentMArea()->getCursor()->getWorldPosition());
    }
}

void MLocation::loadAdjacentMAreas() {
    sf::Vector2i areaLoc = getCurrentMArea()->getHeldArea()->getLocationalPosition();

    if(areaLoc.y > 0){
        chunk.at(1).at(0) = getArea(areaLoc.x, areaLoc.y - 1);
        if(chunk.at(1).at(0) != nullptr){
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            chunk.at(1).at(0)->getHeldArea()->resetRenderPos(0, yOffset);
        }
    }
    else {
        chunk.at(1).at(0) = nullptr;
    }

    if(areaLoc.x < (dimensions.x - 1)){
        chunk.at(2).at(1) = getArea(areaLoc.x + 1, areaLoc.y);
        if(chunk.at(2).at(1) != nullptr){
            chunk.at(2).at(1)->getHeldArea()->resetRenderPos(CONSTANTS::AREA_WIDTH, 0);
        }
    }
    else {
        chunk.at(2).at(1) = nullptr;
    }

    if(areaLoc.y < (dimensions.y - 1)){
        chunk.at(1).at(2) = getArea(areaLoc.x, areaLoc.y + 1);
        if(chunk.at(1).at(2) != nullptr){
            chunk.at(1).at(2)->getHeldArea()->resetRenderPos(0, CONSTANTS::AREA_HEIGHT);
        }
    }
    else {
        chunk.at(1).at(2) = nullptr;
    }

    if(areaLoc.x > 0){
        chunk.at(0).at(1) = getArea(areaLoc.x - 1, areaLoc.y);
        if(chunk.at(0).at(1) != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            chunk.at(0).at(1)->getHeldArea()->resetRenderPos(xOffset, 0);
        }
    }
    else {
        chunk.at(0).at(1) = nullptr;
    }

    if((areaLoc.x < (dimensions.x - 1)) && areaLoc.y > 0){
        chunk.at(2).at(0) = getArea(areaLoc.x + 1, areaLoc.y - 1);
        if(chunk.at(2).at(0) != nullptr){
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            chunk.at(2).at(0)->getHeldArea()->resetRenderPos(CONSTANTS::AREA_WIDTH, yOffset);
        }
    }
    else{
        chunk.at(2).at(0) = nullptr;
    }

    if((areaLoc.x < (dimensions.x - 1)) && (areaLoc.y < (dimensions.y - 1))){
        chunk.at(2).at(2) = getArea(areaLoc.x + 1, areaLoc.y + 1);
        if(chunk.at(2).at(2) != nullptr){
            chunk.at(2).at(2)->getHeldArea()->resetRenderPos(CONSTANTS::AREA_WIDTH, CONSTANTS::AREA_HEIGHT);
        }
    }
    else{
        chunk.at(2).at(2) = nullptr;
    }

    if(areaLoc.x > 0 && (areaLoc.y < (dimensions.y - 1))){
        chunk.at(0).at(2) = getArea(areaLoc.x - 1, areaLoc.y + 1);
        if(chunk.at(0).at(2) != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            chunk.at(0).at(2)->getHeldArea()->resetRenderPos(xOffset, CONSTANTS::AREA_HEIGHT);
        }
    }
    else{
        chunk.at(0).at(2) = nullptr;
    }

    if(areaLoc.x > 0 && areaLoc.y > 0){
        chunk.at(0).at(0) = getArea(areaLoc.x - 1, areaLoc.y - 1);
        if(chunk.at(0).at(0) != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            chunk.at(0).at(0)->getHeldArea()->resetRenderPos(xOffset, yOffset);
        }
    }
    else{
        chunk.at(0).at(0) = nullptr;
    }
}

std::shared_ptr<Location> &MLocation::getHeldLocation() {
    return heldLocation;
}
