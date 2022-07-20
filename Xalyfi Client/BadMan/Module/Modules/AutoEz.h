#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class AutoEz : public IModule {
public:
	AutoEz();
	~AutoEz();

	int counter = 0;
	bool foundPlayer = false;
	bool isDead = false;
	std::string RandMessage;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
