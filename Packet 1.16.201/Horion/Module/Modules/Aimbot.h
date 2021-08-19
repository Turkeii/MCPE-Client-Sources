#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Aimbot : public IModule {
private:
	float range = 8.f;
	bool vertical = true;
	bool sword = false;
	bool click = true;
	float horizontalspeed = 90.f;
	float verticalspeed = 90.f;
	float verticalrange = 180.f;
	float horizontalrange = 180.f;
	bool lock = false;

public:
	Aimbot();
	~Aimbot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
