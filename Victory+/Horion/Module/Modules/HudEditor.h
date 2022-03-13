#pragma once
#include "Module.h"

class HudEditor : public IModule {
public:
	HudEditor();
	~HudEditor();

	float invX = 100.f;
	float invY = 200.f;

	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable();
};