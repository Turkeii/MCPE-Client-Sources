#include "ConfigCommand.h"

ConfigCommand::ConfigCommand() : IMCCommand("config", "Load/save configs", "<load/new/save> <name>") {
	registerAlias("c");
}

ConfigCommand::~ConfigCommand() {
}

bool ConfigCommand::execute(std::vector<std::string>* args) {
	static auto partner = moduleMgr->getModule<Partner>();
	if (args->at(1) == "load") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, false);
		return true;
	} else if (args->at(1) == "new") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, true);
		return true;
	} else if (args->at(1) == "save") {
		configMgr->saveConfig();
		if (partner->Partnered.selected == 0)
			clientMessageF("%s%s[%sSurge%s] %sSuccessfully saved config %s%s%s!", ITALIC, BOLD, BLUE, WHITE, BLUE, WHITE, configMgr->currentConfig.c_str(), WHITE);
		else
		clientMessageF("[%sNG%s] %sSuccessfully saved config %s%s%s!", GOLD, WHITE, LIGHT_PURPLE, GRAY, configMgr->currentConfig.c_str(), LIGHT_PURPLE);
		return true;
	}
	return false;
}