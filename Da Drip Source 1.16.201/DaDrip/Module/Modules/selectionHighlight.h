#pragma once
#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class selectionHighlight : public IModule {
public:
	bool selectRainbow = true;
	float thickness = 1.f;
	float rSelect = 1.f;
	float gSelect = 1.f;
	float bSelect = 1.f;
	bool faceH = true;
	bool doOutline = true;
	float opacityVal = 1.f;
	float fOpacity = 0.5f;
	selectionHighlight();
	~selectionHighlight();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};