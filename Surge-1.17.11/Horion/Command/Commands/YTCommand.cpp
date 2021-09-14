#include "YTCommand.h"

YTCommand::YTCommand() : IMCCommand("yt", "youtube", "Youtube") {
}

YTCommand::~YTCommand() {
}

bool YTCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	clientMessageF("Sub To Joseph Naples On YT");
	return true;
}
