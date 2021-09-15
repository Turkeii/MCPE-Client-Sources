#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class EchestAura : public IModule {
private:
	int range = 70;

public:
	C_MoveInputHandler* inputHandler = nullptr;
	EchestAura();
	~EchestAura();

	std::vector<vec3_ti> chestlist;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
