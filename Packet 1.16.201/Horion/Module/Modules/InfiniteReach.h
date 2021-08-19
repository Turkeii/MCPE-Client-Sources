#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class InfiniteReach : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool isMulti = true;

public:
	float range = 250;
	InfiniteReach();
	~InfiniteReach();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
