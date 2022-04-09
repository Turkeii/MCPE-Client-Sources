#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Aimbot : public IModule {
private:
	bool vertical = true;
	bool sword = false;
	bool click = true;
	float speedAm = 90.f;
	//float verticalspeed = 90.f;
	float rangeAm = 180.f;
	//float horizontalrange = 180.f;

public:
	bool lock = false;
	float range = 8;
	Aimbot();
	~Aimbot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};
