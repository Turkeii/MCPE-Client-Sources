#include "NameSpoofCommand.h"
#include "pch.h"

NameSpoofCommand::NameSpoofCommand() : IMCCommand("namespoof", "Spoof your name on realms/bds", "<name/reset> <name>") {
	registerAlias("ns");
	registerAlias("fakename");
}

bool NameSpoofCommand::execute(std::vector<std::string>* args) {
	if (args->at(1) == "name" && args->size() > 2) {
		std::ostringstream os;
		for (int i = 2; i < args->size(); i++) {
			if (i > 2)
				os << " ";
			os << args->at(i);
		}
		TextHolder* name = new TextHolder(os.str());
		g_Data.setFakeName(name);
		clientMessageF("[Packet] %sSet fakename to %s%s%s, please reconnect!", GREEN, GRAY, name->getText(), GREEN);
		return true;
	} else if (args->at(1) == "reset") {
		g_Data.setFakeName(NULL);
		clientMessageF("[Packet] %sReset fakename!", GREEN);
		return true;
	}
	return false;
}
