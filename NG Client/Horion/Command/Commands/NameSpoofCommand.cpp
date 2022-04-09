#include "NameSpoofCommand.h"
#include "../../Module/ModuleManager.h"

NameSpoofCommand::NameSpoofCommand() : IMCCommand("namespoof", "Spoof your name on realms/bds", "<name/reset> <name>") {
	registerAlias("ns");
	registerAlias("fakename");
}

NameSpoofCommand::~NameSpoofCommand() {
}

bool NameSpoofCommand::execute(std::vector<std::string>* args) {
	static auto partner = moduleMgr->getModule<Partner>();
	if (args->at(1) == "name" && args->size() > 2) {
		std::ostringstream os;
		for (int i = 2; i < args->size(); i++) {
			if (i > 2)
				os << " ";
			os << args->at(i);
		}
		TextHolder* name = new TextHolder(os.str());
		g_Data.setFakeName(name);
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sSet fakename to %s%s%s, please reconnect!", GOLD, WHITE, BLUE, GRAY, name->getText(), BLUE);
		else
			clientMessageF("[%sNG%s] %sSet fakename to %s%s%s, please reconnect!", GOLD, WHITE, BLUE, GRAY, name->getText(), BLUE);
		return true;
	} else if (args->at(1) == "reset") {
		g_Data.setFakeName(NULL);
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sReset fakename!", GOLD, WHITE, BLUE);
		else
			clientMessageF("[%sNG%s] %sReset fakename!", GOLD, WHITE, BLUE);
		return true;
	}
	return false;
}
