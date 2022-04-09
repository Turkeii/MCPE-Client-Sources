#pragma once
#include "Module.h"
class ChestStealer : public IModule {
public:
	ChestStealer();
	~ChestStealer();

	bool enhanced = true;
	bool dump = false;
	int setDelay = 0;
	int delay = 5;

	// Inherited via IModule
	virtual void chestScreenController_tick(C_ChestScreenController* c);
	virtual const char* getModuleName() override;
};