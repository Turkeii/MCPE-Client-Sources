#include "GameModeCommand.h"

GameModeCommand::GameModeCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GameModeCommand::~GameModeCommand() {
}

bool GameModeCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 2) {
		g_Data.getLocalPlayer()->setGameModeType(gamemode);
		clientMessageF("[%sKaeru Vxint%s] %sGameMode changed!", DARK_PURPLE, WHITE, GREEN);
		return true;
	}

	clientMessageF("[%sKaeru Vxint%s] %sInvalid GameMode!", DARK_PURPLE, WHITE, RED);
	return true;
}
