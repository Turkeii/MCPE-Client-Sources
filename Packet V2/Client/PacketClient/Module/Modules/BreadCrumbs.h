#pragma once

#include "../../DrawUtils.h"
#include "Module.h"

class BreadCrumbs : public IModule {
public:
	std::vector<vec3_t> blockBelow;
	bool clear = false;

	BreadCrumbs();
	~BreadCrumbs();

	// Inherited via IModule
	virtual void onDisable() override;
	virtual void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};