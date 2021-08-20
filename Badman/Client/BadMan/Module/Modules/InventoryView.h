#pragma once
#include "Module.h"

class InventoryView : public IModule {
public:
	InventoryView();
	~InventoryView();
	float xVal = 28.f;
	float invX = 100.f;
	float invY = 100.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};