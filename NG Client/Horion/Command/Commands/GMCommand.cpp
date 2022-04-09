#include "GMCommand.h"
#include "../../Module/ModuleManager.h"

GMCommand::GMCommand() : IMCCommand("gamemode", "Changes the local player's gamemode", "<number>") {
	registerAlias("gm");
}

GMCommand::~GMCommand() {
}

bool GMCommand::execute(std::vector<std::string>* args) {
	static auto partner = moduleMgr->getModule<Partner>();
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	int gamemode = assertInt(args->at(1));
	if (gamemode >= 0 && gamemode <= 2) {
		g_Data.getLocalPlayer()->setGameModeType(gamemode);
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sGamemode Changed!", BLUE, WHITE, BLUE);
		else
			clientMessageF("[%sNG%s] %sGamemode Changed!", LIGHT_PURPLE, WHITE, LIGHT_PURPLE);
		return true;
	}
	if (partner->Partnered.selected == 0)
	clientMessageF("[%sSurge%s] %sInvalid GameMode!", BLUE, WHITE, RED);
	else
		clientMessageF("[%sNG%s] %sInvalid GameMode!", LIGHT_PURPLE, WHITE, RED);
	return true;
}