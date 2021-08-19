#pragma once
#include "Module.h"

class Welcome : public IModule {
public:
	Welcome();
	~Welcome();
	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};