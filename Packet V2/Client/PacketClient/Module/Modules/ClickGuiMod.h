#pragma once
#include "Module.h"

class ClickGuiMod : public IModule {
public:
	static float textR;
	static float textG;
	static float textB;

	static float dtextR;
	static float dtextG;
	static float dtextB;

	static float sliderR;
	static float sliderG;
	static float sliderB;

	static float backroundR;
	static float backroundG;
	static float backroundB;

	ClickGuiMod();
	~ClickGuiMod();

	SettingEnum theme = this;

	bool headerAnimation = false;
	bool openAnimation = false;
	bool showTooltips = false;
	bool rainbowColor = false;
	bool animations = true;
	float opacity = 0.8f;
	int bgCounter = 1;
	float bgOpacity = 0.f;
	bool enabled = true;

	// Inherited via IModule
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};