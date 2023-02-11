#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class ItemTP : public IModule {
public:
	int range = 20;
	int delay = 0;
	vec3_t prevPos;
	int Odelay = 0;

	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName();
	virtual void onDisable() override;
	virtual void onEnable() override;
	ItemTP();
};