#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class Excavator : public IModule {
private:
	bool radius = false;
	bool ores = false;
	int customR = 255;
	int customG = 255;
	int customB = 255;
	int range = 3;
	int up = 1;
	int down = 1; //starts at eye level and goes up and down from there

public:
	Excavator();
	~Excavator();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
