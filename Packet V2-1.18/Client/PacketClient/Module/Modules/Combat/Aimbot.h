#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Aimbot : public IModule {
private:
	float angleAmount = 180.f;
	bool vertical = true;
	float speed = 90.f;
	bool click = true;
	bool lock = false;
public:
	float range = 8.f;

	virtual void onPlayerTick(C_Player* plr);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	virtual void onEnable();
	Aimbot();
};