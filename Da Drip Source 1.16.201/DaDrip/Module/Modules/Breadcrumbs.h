#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Breadcrumbs : public IModule {
private:
	std::vector<vec3_t> linePoints;
	vec3_t startPos;
	vec3_t startPosTop;

public:
	Breadcrumbs();
	~Breadcrumbs();

	// Inherited via IModule
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	void onLevelRender() override;
};