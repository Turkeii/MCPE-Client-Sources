#pragma once
#include "../Module.h"

class Reach : public IModule {
private:
	float reachValue = 8;
	float originalReach = 0;
	float* reachPtr = nullptr;
	unsigned long oldProtect = 0;

public:
	Reach();

	// Inherited via IModule
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onEnable();
	virtual void onDisable();
};
