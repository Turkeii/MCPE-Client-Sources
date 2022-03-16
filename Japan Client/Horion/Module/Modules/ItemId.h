#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class ItemId : public IModule {
private:
	float ItemIdX = 100.f;
	float ItemIdY = 100.f;
	float scale = 1.f;

public:
	ItemId();
	~ItemId();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
