#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class ESP : public IModule {
public:
	bool isMulti = true;
	int delay = 0;
	int Odelay = 0;
	bool isMobEsp = false;
	bool doRainbow = false;
	bool is2d = false;
	bool hurttime = false;
	float range = 100;
	int timer5 = 0;
	ESP();
	~ESP();


	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	/*virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	//virtual void onDisable() override;
	virtual void onLevelRender() override;*/
};
