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
#include <include/quests/questlogic.hpp>

QuestLogic::QuestLogic() {

}

bool QuestLogic::HasThisQuest(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList) {
    for(auto pq : *questList){
        if(pq.getDetails()->getID() == quest->getID()){
            return true;
        }
    }

    return false;
}

bool QuestLogic::CompletedThisQuest(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList) {
    for(auto pq : *questList){
        if(pq.getDetails()->getID() == quest->getID()){
            return pq.isCompleted();
        }
    }

    return false;
}

bool QuestLogic::HasAllQuestCompletionItems(std::shared_ptr<Quest> quest,
                                            std::shared_ptr<std::vector<InventoryItem>> playerInventory) {
    for(auto qci : *quest->getQuestCompletionItems()){
        bool foundItemInInventory = false;

        for(auto item : *playerInventory){
            if(item.getDetails()->getID() == qci.getDetails()->getID()){
                foundItemInInventory = true;

                if(item.getQuantity() < qci.getQuantity()){
                    return false;
                }
            }
        }

        if(!foundItemInInventory){
            return false;
        }
    }

    return true;
}

void QuestLogic::CompleteQuest(std::shared_ptr<Quest> quest) {
    // TODO: quest completion text stuff

    RemoveQuestCompletionItems(quest, MAIN::core.GetPlayer()->getInventory());

    // TODO: quest rewards text stuff

    std::shared_ptr<Player> player = MAIN::core.GetPlayer();

    player->addExpPoints(quest->getRewardExp());
    player->addGold(quest->getRewardGold());
    player->addItemToInventory(quest->getRewardItemID());

    MarkQuestAsCompleted(quest, player->getQuests());
}

void QuestLogic::GiveQuestToPlayer(std::shared_ptr<Quest> quest) {
    // TODO: quest receive stuff

    for(auto qci : *quest->getQuestCompletionItems()){
        if(qci.getQuantity() == 1){
            // TODO: receive single item text
        }
        else{
            // TODO: receive multiple item text
        }
    }

    PlayerQuest pq(quest->getID());
    AddQuestToList(pq, MAIN::core.GetPlayer()->getQuests());
}

void QuestLogic::AddQuestToList(PlayerQuest quest, std::shared_ptr<std::vector<PlayerQuest>> questList) {
    questList->push_back(quest);
}

void QuestLogic::RemoveQuestCompletionItems(std::shared_ptr<Quest> quest,
                                            std::shared_ptr<std::vector<InventoryItem>> playerInventory) {
    for(auto qci : *quest->getQuestCompletionItems()){
        for(auto item : *playerInventory){
            if(item.getDetails()->getID() == qci.getDetails()->getID()){
                item.setQuantity(item.getQuantity() - qci.getQuantity());
                break;
            }
        }
    }
}

void
QuestLogic::MarkQuestAsCompleted(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList) {
    for(auto pq : *questList){
        if(pq.getDetails()->getID() == quest->getID()){
            pq.setCompleted();
            return;
        }
    }
}
