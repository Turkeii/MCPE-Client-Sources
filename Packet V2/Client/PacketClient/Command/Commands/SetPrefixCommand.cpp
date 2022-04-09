#include "SetprefixCommand.h"

SetprefixCommand::SetprefixCommand() : IMCCommand("setprefix", "Set the prefix for commands", "<prefix>") {
	registerAlias("prefix");
}

SetprefixCommand::~SetprefixCommand() {
}

bool SetprefixCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	assertTrue(args->at(1).length() == 1);
	char prefix = args->at(1).at(0);
	cmdMgr->prefix = prefix;
	clientMessageF("[Packet] %sSet prefix to %s%c", GREEN, GRAY, prefix);
	return true;
}