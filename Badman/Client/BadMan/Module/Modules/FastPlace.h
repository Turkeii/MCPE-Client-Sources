#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class FastPlace : public IModule {
public:

	bool onlyCrystals = true;
	float Odelay = 0.f;
	float delay = 0.f;

	FastPlace();
	~FastPlace();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
