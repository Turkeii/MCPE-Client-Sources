#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class XP : public IModule {
private:
	bool levels = true;
	int amount = 1;
public:
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	XP();
};