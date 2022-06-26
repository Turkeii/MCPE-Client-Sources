#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Timer : public IModule {
public:
	int timer = 50;

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	Timer();
};
