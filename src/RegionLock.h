#ifndef MODULE_REGIONLOCK
#define MODULE_REGIONLOCK

class RegionLockPlayerScript : public PlayerScript
{
public:
    RegionLockPlayerScript() : PlayerScript("RegionLockPlayerScript") { }
	
private:
    void OnUpdateArea(Player* player, uint32 oldArea, uint32 newArea) override;
};

class RegionLockWorldScript : public WorldScript
{
public:
	RegionLockWorldScript() : WorldScript("RegionLockWorldScript") { }

private:
	void OnAfterConfigLoad(bool reload) override;
};

#endif