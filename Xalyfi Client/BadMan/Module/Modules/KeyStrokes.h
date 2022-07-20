#pragma once
#include "Module.h"
class KeyStrokes : public IModule {
public:
	KeyStrokes();
	~KeyStrokes();

	float keystrokesX = 9.f;
	float keystrokesY = 9.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
