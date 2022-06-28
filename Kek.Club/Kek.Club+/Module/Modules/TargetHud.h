#pragma once
#include "Module.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
class TargetHud : public IModule {
public:
	TargetHud();
	~TargetHud();
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* ctx) override;
};