#include "SetPrefixCommand.h"

SetPrefixCommand::SetPrefixCommand() : IMCCommand("setprefix", "Set the prefix for horion commands", "<prefix>") {
	registerAlias("prefix");
}

SetPrefixCommand::~SetPrefixCommand() {
}

bool SetPrefixCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	assertTrue(args->at(1).length() == 1);
	char prefix = args->at(1).at(0);
	cmdMgr->prefix = prefix;
	clientMessageF("[%sKaeru Vxint%s] %sSet prefix to %s%c", DARK_PURPLE, WHITE, GREEN, GRAY, prefix);
	return true;
}
