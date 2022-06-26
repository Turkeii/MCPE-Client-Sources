#pragma once
#include "Module.h"

class ConfigManagerMod : public IModule {
public:
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onLoadConfig(void* conf);
	virtual void onSaveConfig(void* conf);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual bool allowAutoStart();
	virtual void onDisable();
	virtual void onEnable();
	ConfigManagerMod();
};