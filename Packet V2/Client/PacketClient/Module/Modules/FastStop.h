#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class FastStop : public IModule {
private:
	bool icey = false;
	int counter = 1;

public:
	FastStop();
	~FastStop();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};