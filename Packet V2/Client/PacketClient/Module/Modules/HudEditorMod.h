#pragma once

#include "Module.h"

class HudEditorMod : public IModule {
public:
	bool initialized = false;
	int timesRendered2 = 0;

	HudEditorMod();
	~HudEditorMod();

	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	//virtual void onLoadConfig(void* conf) override;
	//virtual void onSaveConfig(void* conf) override;
};