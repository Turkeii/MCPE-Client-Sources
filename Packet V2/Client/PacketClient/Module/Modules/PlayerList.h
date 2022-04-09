#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class PlayerList : public IModule {
public:
	float range = 255;

	PlayerList();
	~PlayerList();

	virtual bool isFlashMode() override;
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};