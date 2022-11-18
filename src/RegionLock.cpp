/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

std::vector<uint32> unlockedAreas;

// Add player scripts
class RegionLockPlayerScript : public PlayerScript
{
public:
    RegionLockPlayerScript() : PlayerScript("RegionLockPlayerScript") { }

private:
    void OnUpdateArea(Player* player, uint32 oldArea, uint32 newArea) override
    {
		if(oldArea == newArea)
		{
			return;
		}
		
        if (!std::count(unlockedAreas.begin(), unlockedAreas.end(), newArea))
        {
            player->TeleportTo(player->m_homebindMapId, player->m_homebindX, player->m_homebindY, player->m_homebindZ, player->m_homebindO);
			ChatHandler(player->GetSession()).SendSysMessage("Sorry, this area is not yet unlocked.");
        }
    }
};

// Add all scripts in one
void AddRegionLockScripts()
{
	//Elwynn Forest
    unlockedAreas.push_back(9); //Northshire Valley
	unlockedAreas.push_back(24); //Northshire River
	unlockedAreas.push_back(24); //Northshire Abbey
	unlockedAreas.push_back(34); //Echo Ridge Mine
	unlockedAreas.push_back(59); //Northshire Vineyard

    new RegionLockPlayerScript();
}
