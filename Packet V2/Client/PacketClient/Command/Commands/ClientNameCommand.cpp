#include "ClientNameCommand.h"

#include "../../Module/ModuleManager.h"

ClientNameCommand::ClientNameCommand() : IMCCommand("clientname", "Edit Clients Name", "<set/reset> <name>") {
	registerAlias("watermark");
	registerAlias("name");
}

ClientNameCommand::~ClientNameCommand() {
}

bool ClientNameCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);
	auto watermark = moduleMgr->getModule<Watermark>();

	if (args->at(1) == "set" && args->size() > 2) {
		std::ostringstream os;
		for (int i = 2; i < args->size(); i++) {
			if (i > 1)
				os << " ";
			os << args->at(i);
		}
		std::string text = os.str().substr(1);
		if (watermark->firstLetter) clientMessageF("[Packet] %sFailed to set the name! (Turn off FirstLetter)", RED);
		else {
			watermark->getMessage() = text;
			clientMessageF("[Packet] %sName set to %s%s%s!", GREEN, GRAY, text.c_str(), GREEN);
		}
		return true;
	} else if (args->at(1) == "reset") {
		watermark->getMessage() = "Packet Client";
		clientMessageF("[Packet] %sReset!", GREEN);
		return true;
	}
	return false;
}