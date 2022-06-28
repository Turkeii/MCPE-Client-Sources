#include "ClickGuiMod.h"
#include "../../Menu/ClickGui.h"
int ClickGuiMod::rFloat{255};
 int ClickGuiMod::gFloat{255};
 int ClickGuiMod::bFloat{255};
ClickGuiMod::ClickGuiMod() : IModule(VK_INSERT, Category::HUD, "swag custom gui") {
	registerBoolSetting("Show Tooltips", &showTooltips, showTooltips);
	registerBoolSetting("Rainbow", &rainbow, rainbow);
	registerIntSetting("Red", &rFloat, rFloat, 0, 255);
	registerIntSetting("Green", &gFloat, gFloat, 0, 255);
	registerIntSetting("Blue", &bFloat, bFloat, 0, 255);
	registerFloatSetting("Opacity", &this->opacity, this->opacity, 0.3f, 1.f);
}

ClickGuiMod::~ClickGuiMod() {
}

const char* ClickGuiMod::getModuleName() {
	return ("Gui");
}

void ClickGuiMod::onEnable() {
	g_Data.getClientInstance()->releaseMouse();
}

bool ClickGuiMod::allowAutoStart() {
	return false;
}

void ClickGuiMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
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
