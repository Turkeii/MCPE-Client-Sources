#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	bool iszephyr = false;
	bool betterESP = true;
	bool circle = true;
	bool item = true;

	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onLevelRender() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};