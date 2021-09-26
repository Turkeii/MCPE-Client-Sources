#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class AutoClicker : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool weapons = true;
	bool breakBlocks = true;
	bool rightclick = false;
	bool hold = false;

	bool jitter = true;
	int xJitter = 5;
	int yJitter = 5;

	bool doRand = true;
	int minRand = 15;
	int maxRand = 20;

public:
	AutoClicker();
	~AutoClicker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};