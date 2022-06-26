#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class AutoClicker : public IModule {
private:
	bool weapons = false;
	bool hold = true;
	int maxCPS = 20;
	int minCPS = 15;
	int CPS = 0;
public:
	virtual void onPlayerTick(C_Player* plr);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	AutoClicker();
};
