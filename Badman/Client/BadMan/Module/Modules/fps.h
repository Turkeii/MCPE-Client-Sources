#pragma once
#include "Module.h"

class fps : public IModule {
public:
	fps();
	~fps();

	float scale = 1.f;
	float fpsX = 100.f;
	float fpsY = 100.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};