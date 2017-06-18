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

#include <include/item/item.hpp>
#include <include/item/inventoryitem.hpp>

#include <include/quests/playerquest.hpp>
#include <include/quests/questcompletionitem.hpp>
#include <include/quests/quest.hpp>

#include <memory>

class QuestLogic {
public:
    static bool HasThisQuest(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList);
    static bool CompletedThisQuest(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList);
    static bool HasAllQuestCompletionItems(std::shared_ptr<Quest> quest,
                                           std::shared_ptr<std::vector<InventoryItem>> playerInventory);

    static void CompleteQuest(std::shared_ptr<Quest> quest);
    static void GiveQuestToPlayer(std::shared_ptr<Quest> quest);
private:
    QuestLogic();

    static void AddQuestToList(PlayerQuest quest, std::shared_ptr<std::vector<PlayerQuest>> questList);
    static void RemoveQuestCompletionItems(std::shared_ptr<Quest> quest,
                                           std::shared_ptr<std::vector<InventoryItem>> playerInventory);
    static void MarkQuestAsCompleted(std::shared_ptr<Quest> quest, std::shared_ptr<std::vector<PlayerQuest>> questList);
};