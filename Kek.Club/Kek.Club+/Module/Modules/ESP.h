#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = false;
	bool is2d = false;
	bool itemEsp = true;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	float thickness = 0.2f;
	float misc = 1;
	SettingEnum espType;
	SettingEnum rainBow;
	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onLevelRender() override;
};
