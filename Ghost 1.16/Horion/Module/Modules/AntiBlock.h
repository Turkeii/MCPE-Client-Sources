#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class AntiBlock : public IModule {
private:
	int range = 5;
	bool beds = false;
	bool anvil = false;
	bool anchor = false;
	bool cactus = false;
	bool tnt = false;

public:
	AntiBlock();
	~AntiBlock();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};