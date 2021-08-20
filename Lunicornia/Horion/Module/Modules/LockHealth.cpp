#include "LockHealth.h"

LockHealth::LockHealth()
    : IModule(0x0, Category::EXPLOITS, "") 
{
	this->registerIntSetting("Health", &health, 20, 0, 40);
}
const char* LockHealth::getModuleName()
{
	return ("LockHealth");
}

void LockHealth::onTick(C_GameMode*)
{
	if (this->isEnabled())
	{
		g_Data.getLocalPlayer()->heal(health);
		//g_Data.getLocalPlayer()->setDamageNearbyMobs
	}
}
