#pragma once
#include "Module.h"

class Info : public IModule {
public:
	Info();
	~Info();
	bool tabgui = false;
	bool fps = true;
	bool cps = false;
	bool coordinates = true;
	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};