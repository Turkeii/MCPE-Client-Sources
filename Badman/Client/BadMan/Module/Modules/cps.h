#pragma once
#include "Module.h"

class cps : public IModule {
public:
	cps();
	~cps();

	float scale = 1.f;
	float cpsX = 100.f;
	float cpsY = 100.f;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
