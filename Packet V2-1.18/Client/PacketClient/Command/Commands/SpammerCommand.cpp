#include "SpammerCommand.h"

#include "../../Module/ModuleManager.h"
#include "pch.h"

SpammerCommand::SpammerCommand() : IMCCommand("spammer", "Edit spammer delay/text", "<text/delay/bypass/manual> <string/int/bool>") {
	registerAlias("spam");
}

bool SpammerCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	std::string option = args->at(1);
	std::transform(option.begin(), option.end(), option.begin(), ::tolower);

	auto spammer = moduleMgr->getModule<Spammer>();

	if (option == "text") {
		std::ostringstream os;
		for (int i = 2; i < args->size(); i++) {
			if (i > 1)
				os << " ";
			os << args->at(i);
		}
		std::string text = os.str().substr(1);
		spammer->getMessage() = text;
		clientMessageF("[Packet] %sSpammer message set to %s%s%s!", GREEN, GRAY, text.c_str(), GREEN);
		return true;
	} else if (option == "delay") {
		int delay = assertInt(args->at(2));
		if (delay < 1) {
			clientMessageF("[Packet] %sDelay needs to be 1 or more!", RED);
			return true;
		} else {
			spammer->getDelay() = delay;
			return true;
		}
	} else if (option == "bypass") {
		std::string data = args->at(2);
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		bool state = (data == "true") ? true : false;
		spammer->getBypass() = state;
		clientMessageF("[Packet] %sBypass set to %s%s%s!", GREEN, GRAY, state ? "true" : "false", GREEN);
		return true;
	} else if (option == "manual") {
		int times = assertInt(args->at(2));
		std::ostringstream os;
		for (int i = 3; i < args->size(); i++) {
			if (i > 1)
				os << " ";
			os << args->at(i);
		}
		std::string text = os.str().substr(1);
		for (int i = 0; i < times; i++) {
			C_TextPacket textPacket;
			textPacket.message.setText(text + (spammer->getBypass() ? (" | " + Utils::randomString(8)) : ""));
			textPacket.sourceName = *g_Data.getLocalPlayer()->getNameTag();
			//textPacket.xboxUserId = TextHolder(std::to_string(g_Data.getLocalPlayer()->getUserId()));
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		}
		return true;
	}
	return false;
}