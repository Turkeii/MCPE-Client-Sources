#pragma once
#include "Module.h"
#include "../ModuleManager.h"
class CrosshairPlus : public IModule {
private:
public:
	CrosshairPlus();
	~CrosshairPlus();
	float width = 0.25f;
	float gap = 0.25f;
	float size = 0.25f;
	bool dynamic = false;
	bool isMoving = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};