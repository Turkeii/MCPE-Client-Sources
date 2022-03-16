#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class AutoCrystalKari : public IModule {
public:
	bool onlyCrystals = true;
	float Odelay = 0.f;
	float delay = 0.f;
	bool onclick = true;
	bool silentswitch = false;
	AutoCrystalKari();
	~AutoCrystalKari();
	bool findBlock();
	bool findBlock2();

	bool tryScaffold(vec3_t blockBellow);
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModeName() override;

	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
};
