#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class Interface : public IModule {
public:
	std::string clientName = "Fatality";
	std::string releaseStr = "Release";
	std::string versionStr = "Release Build - 121122";

	std::string& getClientName() { return clientName; };
public:
	// Settings
	bool keystrokes = false;
	float saturation = 1.f;
	bool armorHUD = false;
	bool release = true;
	bool tabGUI = false;
	int opacity = 150;
	bool info = true;
	int spacing = 70;

	float scale = 1.f;

	// Positions
	vec2_t windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	float releaseX = 2.5;
	float releaseY = 2.5;
	float armorX = 2.5;
	float armorY = 60;
	float fpsX = 2.5;
	float fpsY = windowSize.y - 40;
	float bpsX = 2.5f;
	float bpsY = windowSize.y - 30;
	float posX = 2.5f;
	float posY = windowSize.y - 20;

	// Colors
	SettingEnum color = this;
	float r = 255.f, g = 255.f, b = 255.f;
	float r2 = 32.f, g2 = 32.f, b2 = 32.f;

	virtual void onPostRender(C_MinecraftUIRenderContext* renderCtx);
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx);
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	Interface();
};