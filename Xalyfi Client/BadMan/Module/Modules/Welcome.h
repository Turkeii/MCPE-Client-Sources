#pragma once
#include "Module.h"
class Welcome : public IModule {
public:
	Welcome();
	~Welcome();

	float scale = 1.f;
	std::string name = "";
	bool Hello = false;
	bool brooda = false;
	bool badman = true;

	SettingEnum TextMode;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};
