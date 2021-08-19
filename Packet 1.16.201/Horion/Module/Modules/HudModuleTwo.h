#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class HudModuleTwo : public IModule {
public:
	HudModuleTwo();
	~HudModuleTwo();

	bool tabgui = false;
	bool shadowMode = true;

	//flags
	bool alert = true;
	bool flag = false;
	bool flyflag = false;
	bool bhopflag = false;
	bool longjumpflag = false;
	bool scaffoldflag = false;
	//
	bool textShadow = true;
	bool versionMode = false;
	bool arraylist = true;
	bool arraylistOutline = true;
	bool arraylistBackground = true;
	bool rainbow = false;
	bool clickToggle = true;
	bool watermark = true;
	bool coordinates = false;
	bool keybinds = true;
	bool displayArmor = false;
	bool keystrokes = false;
	bool fps = false;
	bool cps = false;
	bool alwaysShow = false;
	float fpspos = 1.f;
	float fpspos2 = 1.f;
	float cpspos = 1.f;
	float cpspos2 = 1.f;

	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};