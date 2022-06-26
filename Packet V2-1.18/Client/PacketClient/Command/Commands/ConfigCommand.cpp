#include "ConfigCommand.h"
#include "pch.h"

ConfigCommand::ConfigCommand() : IMCCommand("config", "Load/save configs", "<load/new/save> <name>") {
	registerAlias("cnfg");
	registerAlias("cfg");
	registerAlias("c");
}

bool ConfigCommand::execute(std::vector<std::string>* args) {
	if (args->at(1) == "load" || args->at(1) == "l") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, false);
		SettingMgr->loadSettings("Settings", false);
		return true;
	} else if (args->at(1) == "new" || args->at(1) == "n") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, true);
		SettingMgr->loadSettings("Settings", true);
		return true;
	} else if (args->at(1) == "save" || args->at(1) == "s") {
		configMgr->saveConfig();
		SettingMgr->saveSettings();
		clientMessageF("[Packet] %sSuccessfully saved config %s%s%s!", GREEN, GRAY, configMgr->currentConfig.c_str(), GREEN);
		clientMessageF("[Packet] %sSuccessfully saved %s%s%s!", GREEN, GRAY, SettingMgr->currentSettings.c_str(), GREEN);
		return true;
	}
	return false;
}