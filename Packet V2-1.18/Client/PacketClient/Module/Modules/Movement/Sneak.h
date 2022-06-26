#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Sneak : public IModule {
public:
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	Sneak();
};