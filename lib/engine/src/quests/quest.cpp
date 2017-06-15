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

#include <include/quests/quest.hpp>

Quest::Quest(int id, std::string in_name, std::string descrip, int rewardExp, int rewardG,
             std::vector<QuestCompletionItem> qci, int rewardItem) {
    ID = id;
    name = in_name;
    description = descrip;
    rewardExperience = rewardExp;
    rewardGold = rewardG;
    questCompletionItems = qci;
    rewardItemID = rewardItem;
}

int Quest::getID() {
    return ID;
}

int Quest::getRewardExp() {
    return rewardExperience;
}

int Quest::getRewardGold() {
    return rewardGold;
}

int Quest::getRewardItemID() {
    return rewardItemID;
}

std::string Quest::getName() {
    return name;
}

std::string Quest::getDescription() {
    return description;
}

std::vector<QuestCompletionItem> Quest::getQuestCompletionItems() {
    return questCompletionItems;
}
