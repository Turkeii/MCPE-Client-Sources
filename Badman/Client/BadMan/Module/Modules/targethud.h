#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Targethud : public IModule {
public:
	Targethud();
	~Targethud();
	int timer8 = 0;
	int timer7 = 0;
	float xVal = 28.f;
	float invX = 100.f;
	float invY = 100.f;
	float Opacity = 1.f;
	bool armor = false;
	bool health = false;
	bool distance = false;
	bool name = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};