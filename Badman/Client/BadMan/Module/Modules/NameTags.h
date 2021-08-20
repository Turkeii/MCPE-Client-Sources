#pragma once

#include "Module.h"

class NameTags : public IModule {
public:
	std::set<std::string> nameTags;
	bool displayArmor = true;
	bool displayhealth = true;
	int customR = 255;
	int customG = 255;
	int customB = 255;

	static float opacity;

	NameTags();
	~NameTags();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
