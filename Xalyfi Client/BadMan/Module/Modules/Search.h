#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class Search : public IModule {
private:
	float thick = 0.35f;
	bool outline = true;
	bool chest = false;
	bool trapped_chest = false;
	bool ender_chest = false;
	bool shulker_box = false;
	bool barrel = false;
	bool dropper = false;
	bool dispenser = false;
	bool hopper = false;
	bool furnace = false;
	int range = 15;
	int Odelay = 0;
	float delay = 0.14f;

public:
	Search();
	~Search();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};