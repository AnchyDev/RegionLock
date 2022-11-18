/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

#include "RegionLock.h"

std::vector<uint32> unlockedAreas;
bool loaded;

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
		unlockedAreas.clear();
	}
	
	QueryResult qResult = WorldDatabase.Query("SELECT AreaId FROM woc_regionlock_area");
	
	if (!qResult)
    {
        LOG_INFO("module", "Failed to load 'woc_regionlock_area' table from world database.");
		loaded = false;
        return;
    }
	
	do
    {
        Field* fields = qResult->Fetch();
		
        uint32 areaId = fields[0].Get<uint32>();
		unlockedAreas.push_back(areaId);
		LOG_INFO("module", "Loading AreaId {}", areaId);
		
    } while (qResult->NextRow());
	
	loaded = true;
	
	LOG_INFO("module", "Finished loading RegionLock.");
}

// Add all scripts in one
void AddRegionLockScripts()
{
	new RegionLockWorldScript();
	
	if(loaded)
	{
		new RegionLockPlayerScript();
	}
}
