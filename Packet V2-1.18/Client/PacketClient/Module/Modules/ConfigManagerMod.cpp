#include "ConfigManagerMod.h"

#include "../../Menu/ConfigManagerMenu.h"
#include "pch.h"

ConfigManagerMod::ConfigManagerMod() : IModule(0, Category::UNUSED, "Maneg Ur Conf") {
	shouldHide = true;
}

const char* ConfigManagerMod::getModuleName() {
	return ("ConfigManager");
}

bool ConfigManagerMod::allowAutoStart() {
	return false;
}

void ConfigManagerMod::onEnable() {
	g_Data.getClientInstance()->releaseMouse();
}

void ConfigManagerMod::onTick(C_GameMode* gm) {
	shouldHide = true;
}

void ConfigManagerMod::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	if (GameData::canUseMoveKeys()) g_Data.getClientInstance()->releaseMouse();
}

void ConfigManagerMod::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
}

void ConfigManagerMod::onDisable() {
	g_Data.getClientInstance()->grabMouse();
}

void ConfigManagerMod::onLoadConfig(void* conf) {
	//IModule::onLoadConfig(conf);
	//ConfigManager::onLoadSettings(conf);
}
void ConfigManagerMod::onSaveConfig(void* conf) {
	//ConfigManager::onSaveSettings(conf);
}