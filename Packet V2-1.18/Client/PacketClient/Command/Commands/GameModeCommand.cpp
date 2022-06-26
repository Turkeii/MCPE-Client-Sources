#include "GameModeCommand.h"
#include "pch.h"

GameModeCommand::GameModeCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

bool GameModeCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 2) {
		g_Data.getLocalPlayer()->setGameModeType(gamemode);
		clientMessageF("[Packet] %sGameMode changed!", GREEN);
		return true;
	}

	clientMessageF("[Packet] %sInvalid GameMode!", RED);
	return true;
}
