#pragma once
#include "Module.h"
class Coordinates : public IModule {
public:
	Coordinates();
	~Coordinates();

	float scale = 1.f;
	float coordsX = 412.f;
	float coordsY = 314.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
