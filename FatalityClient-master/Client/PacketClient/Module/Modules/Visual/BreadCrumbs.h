#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class BreadCrumbs : public IModule {
private:
	std::vector<vec3_t> blockBelow;
	bool clear = false;
public:
	SettingEnum mode = this;

	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onLevelRender();
	virtual void onDisable();
	BreadCrumbs();
};