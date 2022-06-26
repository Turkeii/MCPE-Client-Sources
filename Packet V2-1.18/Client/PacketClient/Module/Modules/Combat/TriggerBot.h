#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class TriggerBot : public IModule {
private:
	int APS = 11;
public:
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	TriggerBot();
};