#pragma once
#include "Module.h"

class InventoryView : public IModule {
public:
	InventoryView();
	~InventoryView();
	SettingEnum rainBow;
	bool rainbow = false;
	bool pastel = false;
	float xVal = 28.f;
	float invX = 100.f;
	float invY = 100.f;
	static float rFloat;
	static float bFloat;
	static float gFloat;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};