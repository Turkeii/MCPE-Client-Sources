#pragma once
#include "ICommand.h"

class ServerCommand : public IMCCommand {
public:
	ServerCommand() : IMCCommand("server", "Show information about the server you're playing on", "") {
		registerAlias("ip");
	}
	~ServerCommand(){};

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override {
		assertTrue(g_Data.getLocalPlayer() != nullptr);
		if (g_Data.getRakNetInstance()->isonaServer())
			clientMessageF("You're currently playing on:\nIP:\nPort: %s", g_Data.getRakNetInstance()->serverIp.getText(), std::to_string(g_Data.getRakNetInstance()->serverPort).c_str());
		else
			clientMessageF("%sYou're not playing on a server.", RED);
		return true;
	}
};