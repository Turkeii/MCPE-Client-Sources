#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	bool itemEsp = true;
	bool friendEsp = true;
	int customR = 255;
	int customG = 255;
	int customB = 255;

	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
//r