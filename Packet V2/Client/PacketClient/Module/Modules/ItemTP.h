#pragma once

#include "Module.h"

class ItemTP : public IModule {
public:
	int range = 20;
	int delay = 0;
	vec3_t prevPos;
	int Odelay = 0;

	ItemTP();
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
};