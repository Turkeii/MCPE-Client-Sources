#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class HoleEsp : public IModule {
private:
	bool obsidian = true;
	bool bedrock = true;
	//bool Check = true;
	int Odelay = 0;
	float delay = 0.14f;
	bool box = false;
	float Opacity = 1.f;

public:
	int range = 5;
	float LineSize = 0.4f;

	HoleEsp();
	~HoleEsp();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	//virtual const char* getModName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	//virtual void onTick(C_GameMode* gm) override;
	//virtual const char* getRawModuleName() override;
};
