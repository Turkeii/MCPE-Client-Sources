#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class BlockOutline : public IModule {
private:
	float red, green, blue = 1.f;
	bool rainbow = false;
	float width = 0.5f;
public:
	SettingEnum mode = this;

	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual const char* getModuleName();
	BlockOutline();
};