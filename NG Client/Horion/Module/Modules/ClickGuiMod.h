#pragma once
#include "Module.h"

class ClickGuiMod : public IModule {
public:
	SettingEnum type;
	SettingEnum Fonts;
	ClickGuiMod();
	~ClickGuiMod();

	static float rcolor;
	static float gcolor;
	static float bcolor;

	static float trcolor;
	static float tgcolor;
	static float tbcolor;

	static float tfrcolor;
	static float tfgcolor;
	static float tfbcolor;

	bool showTooltips = true;
	bool RGB = false;
	int font = 9;
	float opacity = 0.20f;

	// Inherited via IModule
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};
