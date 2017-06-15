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

#include <vector>
#include "questcompletionitem.hpp"

class Quest {
public:
    Quest(int id, std::string in_name, std::string descrip, int rewardExp, int rewardG,
          std::vector<QuestCompletionItem> qci, int rewardItem);

    int getID();
    int getRewardExp();
    int getRewardGold();
    int getRewardItemID();

    std::string getName();
    std::string getDescription();

    std::vector<QuestCompletionItem> getQuestCompletionItems();

private:
    int ID, rewardExperience, rewardGold, rewardItemID;
    std::string name, description;

    std::vector<QuestCompletionItem> questCompletionItems;
};