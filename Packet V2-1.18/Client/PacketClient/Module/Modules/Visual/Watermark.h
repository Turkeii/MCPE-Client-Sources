#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Watermark : public IModule {
private:
	float scale = 1.f;
	int opacity = 150;
	int anim = 0;
public:
	float positionX, positionY = 10;
	bool gradient = true;
	float aidsLen = 0.f;
	float height = 10;

	SettingEnum mode = this;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual const char* getModuleName();
	virtual void onEnable() override;
	Watermark();
};