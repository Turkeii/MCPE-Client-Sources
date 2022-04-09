#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class FastPlace : public IModule {
private:
	int Odelay = 0;
	int delay = 0;

public:
	FastPlace();
	~FastPlace();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
