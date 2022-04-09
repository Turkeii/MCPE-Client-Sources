#include "ClickGuiMod.h"

#include "../../Menu/ClickGui.h"

ClickGuiMod::ClickGuiMod() : IModule(VK_INSERT, Category::VISUAL, "The clickgui - toggle everything by just clicking on it!") {
	registerEnumSetting("Theme", &theme, 1);
	theme.addEntry("Packet", 0);
	theme.addEntry("Fadeaway", 1);
	registerFloatSetting("Opacity", &opacity, opacity, 0.05f, 1.f);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	return ("ClickGui");
}

void ClickGuiMod::onEnable() {
	g_Data.getClientInstance()->releaseMouse();
}

void ClickGuiMod::onTick(C_GameMode* gm) {
	// what is this LMAO
	if (theme.getSelectedValue() == 0) {  // packet
		backroundR = 0;
		backroundG = 0;
		backroundB = 0;

		textR = 1;
		textG = 1;
		textB = 1;

		dtextR = 0.40;
		dtextG = 0.40;
		dtextB = 0.40;

		sliderR = 0.32;
		sliderG = 0.32;
		sliderB = 0.32;
	}

	if (theme.getSelectedValue() == 1) {  // fadeaway
		opacity = 1;
		backroundR = 0;
		backroundG = 0;
		backroundB = 0;

		textR = 1;
		textG = 1;
		textB = 1;

		dtextR = 1;
		dtextG = 1;
		dtextB = 1;

		sliderR = 0.32;
		sliderG = 0.32;
		sliderB = 0.32;
	}
}

float ClickGuiMod::textR = 0.f;
float ClickGuiMod::textG = 0.f;
float ClickGuiMod::textB = 0.f;

float ClickGuiMod::dtextR = 0.f;
float ClickGuiMod::dtextG = 0.f;
float ClickGuiMod::dtextB = 0.f;

float ClickGuiMod::sliderR = 0.f;
float ClickGuiMod::sliderG = 0.f;
float ClickGuiMod::sliderB = 0.f;

float ClickGuiMod::backroundR = 0.f;
float ClickGuiMod::backroundG = 0.f;
float ClickGuiMod::backroundB = 0.f;

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
	openAnimation = false;
}

void ClickGuiMod::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys())
		g_Data.getClientInstance()->releaseMouse();
}

void ClickGuiMod::onLoadConfig(void* conf) {
	IModule::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
}
void ClickGuiMod::onSaveConfig(void* conf) {
	IModule::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
}