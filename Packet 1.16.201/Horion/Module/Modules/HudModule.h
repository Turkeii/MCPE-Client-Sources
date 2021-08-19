#pragma once
#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();

	bool tabgui = false;
	bool arraylist = true;
	bool arraylistOutline = true;
	bool arraylistBackground = true;
	float bgOp = 0.2f;
	bool rainbow = false;
	bool clickToggle = true;
	bool watermark = false;
	bool coordinates = false;
	bool keybinds = false;
	bool displayArmor = false;
	bool keystrokes = false;
	bool fps = false;
	bool cps = false;
	bool alwaysShow = false;

	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
};