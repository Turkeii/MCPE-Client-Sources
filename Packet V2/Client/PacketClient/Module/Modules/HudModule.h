#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	SettingEnum color = this;

	bool tabGUI = false;
	bool keystrokes = false;
	bool armorHUD = false;
	bool info = true;

	float opacity = 0.6;
	float scale = 1.f;

	HudModule();
	~HudModule();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};