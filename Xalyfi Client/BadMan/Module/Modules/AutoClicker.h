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

public:
	AutoClicker();
	~AutoClicker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
