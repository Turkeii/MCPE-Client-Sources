#pragma once
#include "Module.h"
class Welcome : public IModule {
public:
	Welcome();
	~Welcome();

	float scale = 1.f;
	bool rainbow = false;
	bool pastel = false;

	std::string name = "";
	bool Hello = false;
	bool brooda = false;
	bool badman = true;

	float r1 = 255.f;
	float g1 = 255.f;
	float b1 = 255.f;

	float r2 = 32.f;
	float g2 = 32.f;
	float b2 = 32.f;

	float sped = 75.f;

	SettingEnum TextMode;
	SettingEnum rainBow;

	static int rFloat;
	static int bFloat;
	static int gFloat;
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};