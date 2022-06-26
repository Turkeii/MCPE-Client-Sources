#include "ServerCommand.h"
#include "pch.h"

ServerCommand::ServerCommand() : IMCCommand("server", "Show information about the server you're playing on", "") {
	registerAlias("ip");
}

bool ServerCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	if (g_Data.getRakNetInstance()->isonaServer())
		clientMessageF("[Packet] You're currently playing on:\nIP: %s\nPort: %s", g_Data.getRakNetInstance()->serverIp.getText(), std::to_string(g_Data.getRakNetInstance()->serverPort).c_str());
	else
		clientMessageF("[Packet] %sYou're not playing on a server.", RED);
	return true;
}
