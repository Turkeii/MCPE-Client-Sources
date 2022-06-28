#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class AutoEZ : public IModule {
public:
	AutoEZ();
	~AutoEZ();

	int counter = 0;
	bool foundPlayer = false;
	bool isDead = false;
	std::string wp2;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};