#pragma once
#include "Module.h"

class Watermark : public IModule {
public:
	Watermark();
	~Watermark();
	bool clickToggle = true;
	bool textShadow = false;
	bool outline = false;
	bool rainbow = false;
	bool outrainbow = false;
	bool noOutline = true;
	bool test = false;
	bool pastel = false;
	static float horizontal;
	static float vertical;
	// bool editHud = false;
	float scale = 1.f;
	float opacity = 0.f;
	SettingEnum rainBow;
	SettingEnum outLine;
	SettingEnum location;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(C_GameMode* gm) override;

	static int rFloat;
	static int bFloat;
	static int gFloat;
};