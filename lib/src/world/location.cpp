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
#include <include/world/location.hpp>

Location::Location(std::string name, int width, int height) {
    locationName = name;
    dimensions.x = width;
    dimensions.y = height;

    initAreaVector();

    initChunk();
}

void Location::initAreaVector() {
    for(unsigned int i = 0; i < dimensions.x; i++){
        areas.push_back(std::vector<std::shared_ptr<Area>>());
        areas.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            areas.at(i).push_back(nullptr);
        }
    }
}

void Location::initChunk() {
    for(unsigned long i = 0; i < 3; i++){
        chunk.push_back(std::vector<std::shared_ptr<Area>>());
        chunk.at(i).reserve(3);

        for(unsigned long j = 0; j < 3; j++){
            chunk.at(i).push_back(nullptr);
        }
    }
}

Location::~Location() {
    areas.clear();
}

sf::Vector2i Location::getDimensions() {
    return dimensions;
}

void Location::placeArea(unsigned int x, unsigned int y, Area area) {
    if((x >= 0) && (x < getDimensions().x) && (y >= 0) && (y < getDimensions().y)){
        area.setLocationalPosition(sf::Vector2i(x, y));
        areas.at(x).at(y) = std::make_shared<Area>(area);
    }
}

const std::shared_ptr<Area> & Location::getArea(int x, int y) {
    return areas.at((unsigned long) x).at((unsigned long) y);
}

std::string Location::getName() {
    return locationName;
}

void Location::setCurrentArea(int x, int y) {
    if(getArea((unsigned int) x, (unsigned int) y) != nullptr){
        std::shared_ptr<Area> currentArea = getArea((unsigned int) x, (unsigned int) y);
        currentArea->resetRenderPos(0, 0);
        chunk.at(1).at(1) = currentArea;
        loadAdjacentAreas();
    }
}
const std::shared_ptr<Area> &Location::getCurrentArea() {
    return chunk.at(1).at(1);
}

void Location::moveToArea(int xOffset, int yOffset) {
    int xTarget = getCurrentArea()->getLocationalPosition().x + xOffset;
    int yTarget = getCurrentArea()->getLocationalPosition().y + yOffset;

    if((xTarget >= 0) && (xTarget < getDimensions().x) && (yTarget >= 0) && (yTarget < getDimensions().y)){
        setCurrentArea(xTarget, yTarget);
        GFX::gfx.forceCenterCamera(getCurrentArea()->getPlayer()->getWorldPosition());
    }
}

void Location::loadAdjacentAreas() {
    sf::Vector2i areaLoc = getCurrentArea()->getLocationalPosition();

    std::shared_ptr<Area> nArea;
    std::shared_ptr<Area> eArea;
    std::shared_ptr<Area> sArea;
    std::shared_ptr<Area> wArea;

    std::shared_ptr<Area> neArea;
    std::shared_ptr<Area> seArea;
    std::shared_ptr<Area> swArea;
    std::shared_ptr<Area> nwArea;

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

void Location::drawChunk() {
    for(auto& innerVec : chunk){
        for(auto& area : innerVec){
            if(area != nullptr){
                area->draw();
            }
        }
    }
}

void Location::movePlayer(int xOffset, int yOffset) {
    std::shared_ptr<Player> player = std::make_shared<Player>(getCurrentArea()->passPlayer());
    int xTarget = player->getWorldPosition().x + xOffset;
    int yTarget = player->getWorldPosition().y + yOffset;

    if(xTarget < 0){
        if(chunk.at(0).at(1) != nullptr){
            if(chunk.at(0).at(1)->movePlayerToThisArea((chunk.at(0).at(1)->getDimensions().x - 1),
                                                       player->getWorldPosition().y, getCurrentArea())){
                moveToArea((-1), 0);
            }
            return;
        }
    }
    else if(xTarget > (getCurrentArea()->getDimensions().x - 1)){
        if(chunk.at(2).at(1) != nullptr){
            if(chunk.at(2).at(1)->movePlayerToThisArea(0, player->getWorldPosition().y, getCurrentArea())){
                moveToArea(1, 0);
            }
            return;
        }
    }


    if(yTarget < 0){
        if(chunk.at(1).at(0) != nullptr){
            if(chunk.at(1).at(0)->movePlayerToThisArea(player->getWorldPosition().x,
                                                       (chunk.at(1).at(0)->getDimensions().y - 1), getCurrentArea())){
                moveToArea(0, (-1));
            }
            return;
        }
    }
    else if(yTarget > (getCurrentArea()->getDimensions().y - 1)){
        if(chunk.at(1).at(2) != nullptr){
            if(chunk.at(1).at(2)->movePlayerToThisArea(player->getWorldPosition().x, 0, getCurrentArea())){
                moveToArea(0, 1);
            }
            return;
        }
    }

    getCurrentArea()->movePlayer(xOffset, yOffset);
}

