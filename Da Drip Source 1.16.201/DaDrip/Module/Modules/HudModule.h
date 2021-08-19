#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();
	
	
	bool alwaysShow = false;
	
	
	//bool editHud = false;
	float scale = 1.f;
	


	// Inherited via IModule
	
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable();
	virtual void onTick(C_GameMode* gm) override;
};
//da drip