#pragma once
#include "Module.h"

class ClickGuiMod : public IModule {
public:
	ClickGuiMod();
	~ClickGuiMod();

	bool showTooltips = true;
	bool rainbow = false;
	float opacity = 0.f;
	static int rFloat;
	static int bFloat;
	static int gFloat;
	float ClickGuiMod::textR = 0.f;
	float ClickGuiMod::textG = 0.f;
	float ClickGuiMod::textB = 0.f;
	float ClickGuiMod::dtextR = 0.f;
	float ClickGuiMod::dtextG = 0.f;
	float ClickGuiMod::dtextB = 0.f;
	float ClickGuiMod::sliderR = 0.f;
	float ClickGuiMod::sliderG = 0.f;
	float ClickGuiMod::sliderB = 0.f;
	float ClickGuiMod::backroundR = 0.f;
	float ClickGuiMod::backroundG = 0.f;
	float ClickGuiMod::backroundB = 0.f;

	// Inherited via IModule
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};
