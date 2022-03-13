#include "NameSpoofCommand.h"

NameSpoofCommand::NameSpoofCommand() : IMCCommand("namespoof", "Spoof your name on realms/bds", "<name/reset> <name>") {
	registerAlias("ns");
	registerAlias("fakename");
	registerAlias("fn");
}

NameSpoofCommand::~NameSpoofCommand() {
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
		clientMessageF("[%sKaeru Vxint%s] %sSet fakename to %s%s%s, please reconnect!", DARK_PURPLE, WHITE, GREEN, GRAY, name->getText(), GREEN);
		return true;
	} else if (args->at(1) == "reset") {
		g_Data.setFakeName(NULL);
		clientMessageF("[%sKaeru Vxint%s] %sReset fakename!", DARK_PURPLE, WHITE, GREEN);
		return true;
	}
	return false;
}
