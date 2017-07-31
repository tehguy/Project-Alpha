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
#include <include/mapgen/mworld/mlocation.hpp>

#include <iostream>

MLocation::MLocation(std::string name, int width, int height) {
    locationName = name;
    dimensions.x = width;
    dimensions.y = height;

    initAreaVector();
    initChunk();
}

void MLocation::initAreaVector() {
    for(unsigned int i = 0; i < dimensions.x; i++){
        areas.push_back(std::vector<std::shared_ptr<MArea>>());
        areas.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            areas.at(i).push_back(nullptr);
        }
    }
}

void MLocation::initChunk() {
    for(unsigned long i = 0; i < 3; i++){
        chunk.push_back(std::vector<std::shared_ptr<MArea>>());
        chunk.at(i).reserve(3);

        for(unsigned long j = 0; j < 3; j++){
            chunk.at(i).push_back(nullptr);
        }
    }
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
    getCurrentArea()->spawnCursor(0, 0);
}

void MLocation::placeArea(int x, int y, MArea area) {
    if((x >= 0) && (x < getDimensions().x) && (y >= 0) && (y < getDimensions().y)){
        area.setLocationalPosition(sf::Vector2i(x, y));
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
        currentArea->resetRenderPos(0, 0);
        chunk.at(1).at(1) = currentArea;
        loadAdjacentAreas();
    }
}

const std::shared_ptr<MArea> &MLocation::getCurrentArea() {
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
    std::shared_ptr<Cursor> cursor = std::make_shared<Cursor>(getCurrentArea()->passCursor());
    int xTarget = cursor->getWorldPosition().x + xOffset;
    int yTarget = cursor->getWorldPosition().y + yOffset;

    if(xTarget < 0){
        if(chunk.at(0).at(1) != nullptr){
            if(chunk.at(0).at(1)->movePlayerToThisArea((chunk.at(0).at(1)->getDimensions().x - 1),
                                                       cursor->getWorldPosition().y, getCurrentArea())){
                moveToArea((-1), 0);
            }
            return;
        }
    }
    else if(xTarget > (getCurrentArea()->getDimensions().x - 1)){
        if(chunk.at(2).at(1) != nullptr){
            if(chunk.at(2).at(1)->movePlayerToThisArea(0, cursor->getWorldPosition().y, getCurrentArea())){
                moveToArea(1, 0);
            }
            return;
        }
    }


    if(yTarget < 0){
        if(chunk.at(1).at(0) != nullptr){
            if(chunk.at(1).at(0)->movePlayerToThisArea(cursor->getWorldPosition().x,
                                                       (chunk.at(1).at(0)->getDimensions().y - 1), getCurrentArea())){
                moveToArea(0, (-1));
            }
            return;
        }
    }
    else if(yTarget > (getCurrentArea()->getDimensions().y - 1)){
        if(chunk.at(1).at(2) != nullptr){
            if(chunk.at(1).at(2)->movePlayerToThisArea(cursor->getWorldPosition().x, 0, getCurrentArea())){
                moveToArea(0, 1);
            }
            return;
        }
    }

    getCurrentArea()->moveCursor(xOffset, yOffset);
}

void MLocation::moveToArea(int xOffset, int yOffset) {
    int xTarget = getCurrentArea()->getLocationalPosition().x + xOffset;
    int yTarget = getCurrentArea()->getLocationalPosition().y + yOffset;

    if((xTarget >= 0) && (xTarget < getDimensions().x) && (yTarget >= 0) && (yTarget < getDimensions().y)){
        setCurrentArea(xTarget, yTarget);
        GFX::gfx->forceCenterCamera(getCurrentArea()->getCursor()->getWorldPosition());
    }
}

void MLocation::loadAdjacentAreas() {
    sf::Vector2i areaLoc = getCurrentArea()->getLocationalPosition();

    std::shared_ptr<MArea> nArea;
    std::shared_ptr<MArea> eArea;
    std::shared_ptr<MArea> sArea;
    std::shared_ptr<MArea> wArea;

    std::shared_ptr<MArea> neArea;
    std::shared_ptr<MArea> seArea;
    std::shared_ptr<MArea> swArea;
    std::shared_ptr<MArea> nwArea;

    if(areaLoc.y > 0){
        nArea = getArea(areaLoc.x, areaLoc.y - 1);
        if(nArea != nullptr){
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            nArea->resetRenderPos(0, yOffset);
        }
    }
    else {
        nArea = nullptr;
    }

    chunk.at(1).at(0) = nArea;

    if(areaLoc.x < (dimensions.x - 1)){
        eArea = getArea(areaLoc.x + 1, areaLoc.y);
        if(eArea != nullptr){
            eArea->resetRenderPos(CONSTANTS::AREA_WIDTH, 0);
        }
    }
    else {
        eArea = nullptr;
    }

    chunk.at(2).at(1) = eArea;

    if(areaLoc.y < (dimensions.y - 1)){
        sArea = getArea(areaLoc.x, areaLoc.y + 1);
        if(sArea != nullptr){
            sArea->resetRenderPos(0, CONSTANTS::AREA_HEIGHT);
        }
    }
    else {
        sArea = nullptr;
    }

    chunk.at(1).at(2) = sArea;

    if(areaLoc.x > 0){
        wArea = getArea(areaLoc.x - 1, areaLoc.y);
        if(wArea != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            wArea->resetRenderPos(xOffset, 0);
        }
    }
    else {
        wArea = nullptr;
    }

    chunk.at(0).at(1) = wArea;

    if((areaLoc.x < (dimensions.x - 1)) && areaLoc.y > 0){
        neArea = getArea(areaLoc.x + 1, areaLoc.y - 1);
        if(neArea != nullptr){
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            neArea->resetRenderPos(CONSTANTS::AREA_WIDTH, yOffset);
        }
    }
    else{
        neArea = nullptr;
    }

    chunk.at(2).at(0) = neArea;

    if((areaLoc.x < (dimensions.x - 1)) && (areaLoc.y < (dimensions.y - 1))){
        seArea = getArea(areaLoc.x + 1, areaLoc.y + 1);
        if(seArea != nullptr){
            seArea->resetRenderPos(CONSTANTS::AREA_WIDTH, CONSTANTS::AREA_HEIGHT);
        }
    }
    else{
        seArea = nullptr;
    }

    chunk.at(2).at(2) = seArea;

    if(areaLoc.x > 0 && (areaLoc.y < (dimensions.y - 1))){
        swArea = getArea(areaLoc.x - 1, areaLoc.y + 1);
        if(swArea != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            swArea->resetRenderPos(xOffset, CONSTANTS::AREA_HEIGHT);
        }
    }
    else{
        swArea = nullptr;
    }

    chunk.at(0).at(2) = swArea;

    if(areaLoc.x > 0 && areaLoc.y > 0){
        nwArea = getArea(areaLoc.x - 1, areaLoc.y - 1);
        if(nwArea != nullptr){
            int xOffset = (-1) * CONSTANTS::AREA_WIDTH;
            int yOffset = (-1) * CONSTANTS::AREA_HEIGHT;
            nwArea->resetRenderPos(xOffset, yOffset);
        }
    }
    else{
        nwArea = nullptr;
    }

    chunk.at(0).at(0) = nwArea;
}
