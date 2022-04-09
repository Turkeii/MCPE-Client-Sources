#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TargetHUD : public IModule {
public:
	bool hurttime = false;
	int targethud = 0;
	int counter = 0;

	TargetHUD();
	~TargetHUD();

	SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};