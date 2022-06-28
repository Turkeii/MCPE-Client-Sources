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
	SettingEnum enum1;

	float HoleESP::rFloat1{0};
	float HoleESP::gFloat1{255};
	float HoleESP::bFloat1{0};

	float HoleESP::rFloat2{255};
	float HoleESP::gFloat2{0};
	float HoleESP::bFloat2{0};

	float HoleESP::rFloat3{0};
	float HoleESP::gFloat3{255};
	float HoleESP::bFloat3{255};

public:
	int range = 5;
	HoleESP();
	~HoleESP();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	//virtual void onTick(C_GameMode* gm) override;
};
