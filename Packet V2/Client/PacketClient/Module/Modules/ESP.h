#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	bool tracerMode = false;
	ESP();
	~ESP();

	SettingEnum mode = this;

	// Inherited via IModule
	void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};