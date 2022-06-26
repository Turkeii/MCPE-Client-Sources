#pragma once
#include "../../../../Utils/TargetUtil.h"
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class NameTags : public IModule {
public:
	std::set<std::string> nameTags;
	bool displayArmor = true;
	bool underline = true;
	int opacity = 150;

	bool* ingameNametagSetting = nullptr;
	bool gotPrevSetting = false;
	bool lastSetting = true;

	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual const char* getModuleName();
	virtual void onDisable();
	NameTags();
};