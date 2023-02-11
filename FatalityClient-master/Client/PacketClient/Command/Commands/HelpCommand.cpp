#include "HelpCommand.h"
#include "../CommandMgr.h"
#include "pch.h"

HelpCommand::HelpCommand() : IMCCommand("help", "Lists all commands", "") {
	registerAlias("commands");
}

bool HelpCommand::execute(std::vector<std::string>* args) {
	std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();
	clientMessageF("%s-------------------------------------------------------", BOLD);
	for (auto it = commandList->begin(); it != commandList->end(); ++it) {
		IMCCommand* cmds = *it;
		clientMessageF("%s%s%s%s - %s \n", BOLD, cmds->getCommand(), RESET, GRAY, cmds->getDescription());
	}
	clientMessageF("%s-------------------------------------------------------", BOLD);
	return true;
}