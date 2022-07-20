#include "../../Module/ModuleManager.h"
#include "ChatCommand.h"

ChatCommand::ChatCommand() : IMCCommand("chat", "Edit chat message", "<set/reset>") {
}

ChatCommand::~ChatCommand() {
}

bool ChatCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);

	auto chatMod = moduleMgr->getModule<TestModule>();

	if (option == "set") {
		std::ostringstream os;
		for (int i = 2; i < args->size(); i++) {
			if (i > 1)
				os << " ";
			os << args->at(i);
		}
		std::string text = os.str().substr(1);
		chatMod->getMessage() = " | " + text;
		clientMessageF("%sChat message set to %s%s%s!", GREEN, GRAY, text.c_str(), GREEN);
		return true;
	} else if (option == "reset") {
		chatMod->getMessage() = " | Xalyfi";
		clientMessageF("%sChat message reseted!", GREEN);
		return true;
	}
	return false;
}
