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

#include <include/core/core.hpp>
#include <include/core/locationlogic.hpp>

#include <include/quests/questlogic.hpp>

LocationLogic::LocationLogic() {}

void LocationLogic::MoveNorth() {
    std::shared_ptr<Location> locNorth = MAIN::core.getWorld()->GetPlayer()->getCurrentLocation()->getLocationToNorth();
    if(locNorth != nullptr){
        MoveToLocation(locNorth);
    }
}

void LocationLogic::MoveEast() {
    std::shared_ptr<Location> locEast = MAIN::core.getWorld()->GetPlayer()->getCurrentLocation()->getLocationToEast();
    if(locEast != nullptr){
        MoveToLocation(locEast);
    }
}

void LocationLogic::MoveSouth() {
    std::shared_ptr<Location> locSouth = MAIN::core.getWorld()->GetPlayer()->getCurrentLocation()->getLocationToSouth();
    if(locSouth != nullptr){
        MoveToLocation(locSouth);
    }
}

void LocationLogic::MoveWest() {
    std::shared_ptr<Location> locWest = MAIN::core.getWorld()->GetPlayer()->getCurrentLocation()->getLocationToWest();
    if(locWest != nullptr){
        MoveToLocation(locWest);
    }
}

void LocationLogic::MoveToLocation(std::shared_ptr<Location> newLocation) {
    if(!HasRequiredItemToEnter(newLocation)){
        // TODO: print error message stating missing item

        return;
    }
    std::shared_ptr<Player> player = MAIN::core.getWorld()->GetPlayer();
    player->setCurrentLocation(newLocation);

    // TODO: print location name and desc out to whatever GUI comes in later

    player->setCurrentHitpoints(MAIN::core.getWorld()->GetPlayer()->getMaxHitPoints());

    if(newLocation->getQuestAvailableHere() != nullptr){
        if(QuestLogic::HasThisQuest(newLocation->getQuestAvailableHere(), player->getQuests())){
            if(!QuestLogic::CompletedThisQuest(newLocation->getQuestAvailableHere(), player->getQuests())){
                if(QuestLogic::HasAllQuestCompletionItems(newLocation->getQuestAvailableHere(),
                player->getInventory())){
                    QuestLogic::CompleteQuest(newLocation->getQuestAvailableHere());
                }
            }
        }
        else{
            QuestLogic::GiveQuestToPlayer(newLocation->getQuestAvailableHere());
        }
    }

    SetMonsterForCurrentLocation(newLocation);
}

void LocationLogic::SetMonsterForCurrentLocation(std::shared_ptr<Location> location) {
    if(location->getMonsterLivingHere() != nullptr){
        // TODO: display monster description

        std::shared_ptr<Monster> monster = MAIN::core.getWorld()->MonsterByID(location->getMonsterLivingHere()->getID());

        MAIN::core.getWorld()->SetCurrentMonster(monster);
    }
    else {
        MAIN::core.getWorld()->SetCurrentMonster(nullptr);
    }
}

bool LocationLogic::HasRequiredItemToEnter(std::shared_ptr<Location> location) {
    if(location->getItemRequiredToEnter() == nullptr){
        return true;
    }

    for(InventoryItem item : *MAIN::core.getWorld()->GetPlayer()->getInventory()){
        if(item.getDetails()->getID() == location->getItemRequiredToEnter()->getID()){
            return true;
        }
    }

    return false;
}
