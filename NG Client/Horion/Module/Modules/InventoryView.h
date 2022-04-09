#pragma once
#include "Module.h"

class InventoryView : public IModule {
public:
	static float rtext;
	static float gtext;
	static float btext;

	float xVal = 28.f;
	float invX = 0.f;
	float invY = 100.f;
	float opacity = 1.f;
	float scale = 0.75f;
	bool RGB = false;

	InventoryView();
	~InventoryView();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};