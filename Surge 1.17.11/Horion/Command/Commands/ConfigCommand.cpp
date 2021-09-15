#include "ConfigCommand.h"

ConfigCommand::ConfigCommand() : IMCCommand("config", "Load/save configs", "<load/new/save> <name>") {
}

ConfigCommand::~ConfigCommand() {
}

bool ConfigCommand::execute(std::vector<std::string>* args) {
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
		clientMessageF("[%sSurge%s] %sSuccessfully saved config %s%s%s!", BLUE, WHITE, BLUE, WHITE, configMgr->currentConfig.c_str(), WHITE);
		return true;
	}
	return false;
}