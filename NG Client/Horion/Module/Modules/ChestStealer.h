#pragma once
#include "Module.h"
class ChestStealer : public IModule {
public:
	ChestStealer();
	~ChestStealer();

	int delay = 0;
	int setDelay = 0;
	bool enhanced = true;
	bool dump = false;

	// Inherited via IModule
	virtual void chestScreenController_tick(C_ChestScreenController* c);
	virtual const char* getModuleName() override;
};