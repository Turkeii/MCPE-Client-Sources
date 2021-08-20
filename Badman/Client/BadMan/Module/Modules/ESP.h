#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	bool isCustom = true;
	bool itemEsp = true;
	float customR = 1.f;
	float customG = 0.f;
	float customB = 0.f;
	
	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
