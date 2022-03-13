#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Bps : public IModule {
private:
	float bpsX = 100.f;
	float bpsY = 100.f;
	float speed = 0.f;
	float scale = 1.f;

public:
	Bps();
	~Bps();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
