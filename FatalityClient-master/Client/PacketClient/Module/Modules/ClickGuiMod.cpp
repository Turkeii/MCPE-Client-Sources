#include "ClickGUIMod.h"
#include "pch.h"

ClickGUIMod::ClickGUIMod() : IModule(VK_INSERT, Category::VISUAL, "A GUI that displays every module") {
	registerEnumSetting("Theme", &theme, 1);
	theme.addEntry("Test", 0);
	theme.addEntry("Vape", 1);
	theme.addEntry("Astolfo", 2);
	registerEnumSetting("Color", &color, 2);
	color.addEntry("Rainbow", 0);
	color.addEntry("Astolfo", 1);
	color.addEntry("Wave", 2);
	color.addEntry("RGBWave", 3);
	registerBoolSetting("CategoryColors", &categoryColors, categoryColors);
	registerBoolSetting("HudEditor", &showHudEditor, showHudEditor);
	registerBoolSetting("ToolTips", &showTooltips, showTooltips);
	registerBoolSetting("Sounds", &sounds, sounds);
	registerFloatSetting("Red", &r1, r1, 0.f, 255.f);
	registerFloatSetting("Green", &g1, g1, 0.f, 255.f);
	registerFloatSetting("Blue", &b1, b1, 0.f, 255.f);
	registerFloatSetting("Red2", &r2, r2, 0.f, 255.f);
	registerFloatSetting("Green2", &g2, g2, 0.f, 255.f);
	registerFloatSetting("Blue2", &b2, b2, 0.f, 255.f);
	registerIntSetting("Opacity", &opacity, opacity, 0, 255);
	shouldHide = true;
}

const char* ClickGUIMod::getModuleName() {
	return ("ClickGUI");
}

bool ClickGUIMod::allowAutoStart() {
	return false;
}

void ClickGUIMod::onEnable() {
	g_Data.getClientInstance()->releaseMouse();
	openAnim =- 500;
	if (!showHudEditor) hasOpenedGUI = true;
}

void ClickGUIMod::onPlayerTick(C_Player* plr) {
	if (openAnim < 27 && hasOpenedGUI) openAnim += (28 - openAnim) * 0.09f;
}

void ClickGUIMod::onTick(C_GameMode* gm) {
	shouldHide = true;
}

void ClickGUIMod::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!hasOpenedGUI) DrawUtils::drawRectangle(vec4_t(0, 0, g_Data.getClientInstance()->getGuiData()->widthGame, g_Data.getClientInstance()->getGuiData()->heightGame), MC_Color(255, 255, 255), 1.f, 2.f);
	if (GameData::canUseMoveKeys())
		g_Data.getClientInstance()->releaseMouse();
}

void ClickGUIMod::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	if (!hasOpenedGUI) DrawUtils::fillRectangle(vec4_t(0, 0, g_Data.getClientInstance()->getGuiData()->widthGame, g_Data.getClientInstance()->getGuiData()->heightGame), MC_Color(0, 0, 0), 0.3f);
}

void ClickGUIMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
	openAnimation = false;
	hasOpenedGUI = false;
	animation = 1;
}

void ClickGUIMod::onLoadConfig(void* conf) {
	IModule::onLoadConfig(conf);
	ClickGui::onLoadConfig(conf);
	HudEditor::onLoadSettings(conf);
}
void ClickGUIMod::onSaveConfig(void* conf) {
	IModule::onSaveConfig(conf);
	ClickGui::onSaveConfig(conf);
	HudEditor::onSaveSettings(conf);
}