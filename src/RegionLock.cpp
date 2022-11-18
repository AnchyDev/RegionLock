/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

#include "RegionLock.h"

std::vector<uint32> unlockedAreas;

void RegionLockPlayerScript::OnUpdateArea(Player* player, uint32 oldArea, uint32 newArea)
{
	if(oldArea == newArea)
	{
		return;
	}
	
	if(player->isGMChat())
	{
		return;
	}
	
	if (!std::count(unlockedAreas.begin(), unlockedAreas.end(), newArea))
	{
		player->TeleportTo(player->m_homebindMapId, player->m_homebindX, player->m_homebindY, player->m_homebindZ, player->m_homebindO);
		ChatHandler(player->GetSession()).SendSysMessage("Sorry, this area is not yet unlocked.");
	}
}

void RegionLockWorldScript::OnAfterConfigLoad(bool reload)
{
	if(reload)
	{
		return;
	}
	
	LOG_INFO("module", "World Script from RegionLock");
}

// Add all scripts in one
void AddRegionLockScripts()
{
	//Elwynn Forest
    unlockedAreas.push_back(9); //Northshire Valley
	unlockedAreas.push_back(24); //Northshire River
	unlockedAreas.push_back(24); //Northshire Abbey
	unlockedAreas.push_back(34); //Echo Ridge Mine
	unlockedAreas.push_back(59); //Northshire Vineyard

	new RegionLockWorldScript();
    new RegionLockPlayerScript();
}
