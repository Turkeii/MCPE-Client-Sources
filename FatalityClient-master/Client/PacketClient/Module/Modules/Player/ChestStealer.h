#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class ChestStealer : public IModule {
	bool enhanced = true;
	bool dump = false;
	int setDelay = 0;
	int delay = 5;
public:
	std::string name = "ChestStealer";
	bool autoDisable = false;

	virtual void chestScreenController_tick(C_ChestScreenController* c);
	virtual const char* getRawModuleName() override;
	virtual const char* getModuleName() override;
	ChestStealer();
};