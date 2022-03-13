#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class DropperEsp : public IModule {
private:
	float thick = 0.4f;
	bool outline = true;
	bool dropper = true;
	bool chest = false;
	bool tchest = false;
	bool dispenser = false;
	bool kamado = false;
	bool hopper = false;
	bool shulker = false;
	bool barrel = false;
	bool echest = false;
	bool invisBlocks = false;
	bool portalBlocks = false;
	int range = 10;
	int Odelay = 0;
	float delay = 0.14f;

public:
	DropperEsp();
	~DropperEsp();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
