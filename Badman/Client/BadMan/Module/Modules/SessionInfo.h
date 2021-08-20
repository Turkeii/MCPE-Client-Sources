#pragma once
#include "Module.h"

class SessionInfo : public IModule {
public:
	SessionInfo();
	~SessionInfo();
	int gameTick = 0;
	int timer3 = 0;
	int timer4 = 0;
	int timer5 = 0;
	int ticktock = 0;
	bool foundPlayer = false;
	bool isDead = false;
	float xVal = 28.f;
	float invX = 100.f;
	float invY = 100.f;
	float Opacity = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};