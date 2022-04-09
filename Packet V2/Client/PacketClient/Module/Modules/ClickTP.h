#pragma once
#include "../../DrawUtils.h"
#include "Module.h"
class ClickTP : public IModule {
private:
	bool hasClicked = false;
	int timeWaited = 1;
	bool hand = true;
	vec3_t position;

public:
	ClickTP();
	~ClickTP();

	// Inherited via IModule
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};