#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class HoleFiller : public IModule {
private:
	bool spoof = true;
	bool obsidian = true;
	bool bedrock = true;
	int Odelay = 0;
	float delay = 0.14f;

public:
	bool isMobAura = true;
	int range = 5;
	HoleFiller();
	~HoleFiller();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(C_GameMode* gm) override;
};
