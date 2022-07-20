#include "../ModuleManager.h"
#include "AutoConfig.h"

AutoConfig::AutoConfig() : IModule(0, Category::MISC, "Save Config when you click") {
	registerBoolSetting("AutoSaveNotWork", &AutoSave, false);
}

AutoConfig::~AutoConfig() {
}

const char* AutoConfig::getModuleName() {
	return ("AutoConfig");
}

void AutoConfig::onTick(C_GameMode* gm) {
	configMgr->saveConfig();
	clientMessageF("%sXalyfi%s %sSuccessfully saved config %s%s%s!", GOLD, WHITE, GREEN, GRAY, configMgr->currentConfig.c_str(), GREEN);
	static auto AutoConfigMod = moduleMgr->getModule<AutoConfig>();
	AutoConfigMod->setEnabled(false);
}
