#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class BlockOutline : public IModule {
public:
	bool rainbow = false;
	float width = 0.5;
	float red = 1;
	float green = 1;
	float blue = 1;

	SettingEnum mode = this;

	BlockOutline();
	~BlockOutline();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};