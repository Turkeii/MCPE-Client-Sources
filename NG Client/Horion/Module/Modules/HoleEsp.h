#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class HoleESP : public IModule {
private:
	bool obsidian = true;
	bool bedrock = true;
	bool mix = true;
	int Odelay = 0;
	float delay = 0.14f;
	float rSelect = 1.f;
	float gSelect = 0.f;
	SettingEnum enum1;
	float bSelect = 0.f;

	float rSelect1 = 0.f;
	float gSelect1 = 0.f;
	float bSelect1 = 1.f;

	float rSelect2 = 1.f;
	float gSelect2 = 0.f;
	float bSelect2 = 0.f;

public:
	int range = 5;
	HoleESP();
	~HoleESP();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	// virtual void onTick(C_GameMode* gm) override;
};