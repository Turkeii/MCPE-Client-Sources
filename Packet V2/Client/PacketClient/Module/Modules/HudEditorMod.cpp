#include "../../Module/ModuleManager.h"
#include "../../DrawUtils.h"
#include "HudEditorMod.h"

HudEditorMod::HudEditorMod() : IModule(0, Category::CONFIG, "onix client rip off lol") {
}

const char* HudEditorMod::getModuleName() {
	return "HudEditor";
}

HudEditorMod::~HudEditorMod() {
}

// WIP

void HudEditorMod::onEnable() {
	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();
	clickGUI->setEnabled(false);
	g_Data.getClientInstance()->releaseMouse();
}

bool HudEditorMod::allowAutoStart() {
	return false;
}

void HudEditorMod::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (GameData::isKeyDown(*input->spaceBarKey)) {
		setEnabled(false);
	}
}

void HudEditorMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
}

void HudEditorMod::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	DrawUtils::fillRectangle(vec4_t(0, 0, g_Data.getClientInstance()->getGuiData()->widthGame, g_Data.getClientInstance()->getGuiData()->heightGame), MC_Color(0, 0, 0), 0.3);
	if (GameData::canUseMoveKeys())
		g_Data.getClientInstance()->releaseMouse();
}

/*void HudEditorMod::onLoadConfig(void* conf) {
	IModule::onLoadConfig(conf);
	HudEditor::onLoadConfig(conf);
}
void HudEditorMod::onSaveConfig(void* conf) {
	IModule::onSaveConfig(conf);
	HudEditor::onSaveConfig(conf);
}*/