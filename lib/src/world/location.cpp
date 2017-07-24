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

#include <include/core/worldsaver.hpp>
#include <include/gfx/gfx.hpp>

Location::Location(std::string name, int width, int height) {
    locationName = name;
    dimensions.x = width;
    dimensions.y = height;

    for(unsigned int i = 0; i < dimensions.x; i++){
        areas.push_back(std::vector<std::shared_ptr<Area>>());
        areas.at(i).reserve((unsigned long) dimensions.y);

        for(unsigned int j = 0; j < dimensions.y; j++){
            areas.at(i).push_back(nullptr);
        }
    }

    nArea = std::shared_ptr<Area>(nullptr);
    eArea = std::shared_ptr<Area>(nullptr);
    sArea = std::shared_ptr<Area>(nullptr);
    wArea = std::shared_ptr<Area>(nullptr);

    neArea = std::shared_ptr<Area>(nullptr);
    seArea = std::shared_ptr<Area>(nullptr);
    swArea = std::shared_ptr<Area>(nullptr);
    nwArea = std::shared_ptr<Area>(nullptr);
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
        currentArea = getArea((unsigned int) x, (unsigned int) y);
        currentArea->resetRenderPos(0, 0);
        loadAdjacentAreas();
    }
}
const std::shared_ptr<Area> &Location::getCurrentArea() {
    return currentArea;
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

    if(areaLoc.x < (dimensions.x - 1)){
        eArea = getArea(areaLoc.x + 1, areaLoc.y);
        if(eArea != nullptr){
            eArea->resetRenderPos(CONSTANTS::AREA_WIDTH, 0);
        }
    }
    else {
        eArea = nullptr;
    }


    if(areaLoc.y < (dimensions.y - 1)){
        sArea = getArea(areaLoc.x, areaLoc.y + 1);
        if(sArea != nullptr){
            sArea->resetRenderPos(0, CONSTANTS::AREA_HEIGHT);
        }
    }
    else {
        sArea = nullptr;
    }

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

    if((areaLoc.x < (dimensions.x - 1)) && (areaLoc.y < (dimensions.y - 1))){
        seArea = getArea(areaLoc.x + 1, areaLoc.y + 1);
        if(seArea != nullptr){
            seArea->resetRenderPos(CONSTANTS::AREA_WIDTH, CONSTANTS::AREA_HEIGHT);
        }
    }
    else{
        seArea = nullptr;
    }

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
}

void Location::drawChunk() {
    currentArea->draw();

    if(nArea != nullptr){
        nArea->draw();
    }

    if(neArea != nullptr){
        neArea->draw();
    }

    if(eArea != nullptr){
        eArea->draw();
    }

    if(seArea != nullptr){
        seArea->draw();
    }

    if(sArea != nullptr){
        sArea->draw();
    }

    if(swArea != nullptr){
        swArea->draw();
    }

    if(wArea != nullptr){
        wArea->draw();
    }

    if(nwArea != nullptr){
        nwArea->draw();
    }
}

void Location::movePlayer(int xOffset, int yOffset) {
    std::shared_ptr<Player> player = std::make_shared<Player>(currentArea->passPlayer());
    int xTarget = player->getWorldPosition().x + xOffset;
    int yTarget = player->getWorldPosition().y + yOffset;

    if(xTarget < 0){
        if(wArea != nullptr){
            if(wArea->movePlayerToThisArea((wArea->getDimensions().x - 1), player->getWorldPosition().y, currentArea)){
                moveToArea((-1), 0);
                return;
            }
            else{
                return;
            }
        }
    }
    else if(xTarget > (currentArea->getDimensions().x - 1)){
        if(eArea != nullptr){
            if(eArea->movePlayerToThisArea(0, player->getWorldPosition().y, currentArea)){
                moveToArea(1, 0);
                return;
            }
            else{
                return;
            }
        }
    }


    if(yTarget < 0){
        if(nArea != nullptr){
            if(nArea->movePlayerToThisArea(player->getWorldPosition().x, (nArea->getDimensions().y - 1), currentArea)){
                moveToArea(0, (-1));
                return;
            }
            else{
                return;
            }
        }
    }
    else if(yTarget > (currentArea->getDimensions().y - 1)){
        if(sArea != nullptr){
            if(sArea->movePlayerToThisArea(player->getWorldPosition().x, 0, currentArea)){
                moveToArea(0, 1);
                return;
            }
            else{
                return;
            }
        }
    }

    currentArea->movePlayer(xOffset, yOffset);
}

std::string Location::genFileName() {
    std::string filePath = "./save" + locationName + ".map";
    return filePath;
}
