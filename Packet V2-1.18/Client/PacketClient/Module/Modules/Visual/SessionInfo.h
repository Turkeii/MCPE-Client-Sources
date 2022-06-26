#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class SessionInfo : public IModule {
public:
	// dude
	float aidsLen = 0.f;
	bool outline = true;
	int opacity = 150;
	float siY = 10;
	int kills = 0;
	int games = 0;
	float siX = 0;
	int ticks = 0;
	int ticks2 = 0;
	int ticks3 = 0;
	int dead = 1;
	int min = 0;
	int sec = 0;
	int hour = 0;

	SettingEnum mode = this;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	SessionInfo();
};