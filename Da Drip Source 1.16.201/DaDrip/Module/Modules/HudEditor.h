#pragma once
#include "Module.h"

class HudEditor : public IModule {
public:
	HudEditor();
	~HudEditor();


	float pvpX = 0.f;
	float pvpY = 0.f;

	float armorX = 100.f;
	float armorY = 100.f;

	float invX = 100.f;
	float invY = 200.f;

	float arrayX = 100.f;
	float arrayY = 300.f;




	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable();
};