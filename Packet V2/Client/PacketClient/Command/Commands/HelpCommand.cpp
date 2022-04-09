#include "HelpCommand.h"

#include "../CommandMgr.h"

HelpCommand::HelpCommand() : IMCCommand("commands", "Lists all commands", "") {
	registerAlias("command");
	registerAlias("help"); //who tf would call this commands what ---- it lists the commands?
}

HelpCommand::~HelpCommand() {
}

bool HelpCommand::execute(std::vector<std::string>* args) {
	std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();
	for (auto it = commandList->begin(); it != commandList->end(); ++it) {
		IMCCommand* plump = *it;
		clientMessageF("%s%s - %s", plump->getCommand(), GRAY, plump->getDescription());
	}
	return true;
}