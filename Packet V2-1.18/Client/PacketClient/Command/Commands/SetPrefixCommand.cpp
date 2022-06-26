#include "SetprefixCommand.h"
#include "pch.h"

SetprefixCommand::SetprefixCommand() : IMCCommand("setprefix", "Set the prefix for commands", "<prefix>") {
	registerAlias("prefix");
}

bool SetprefixCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	assertTrue(args->at(1).length() == 1);
	char prefix = args->at(1).at(0);
	cmdMgr->prefix = prefix;

	std::string textStr = "Set the prefix to " + std::to_string(prefix);
	//auto notification = g_Data.addNotification("Commands:", textStr);
	//notification->duration = 5;
	return true;
}