#include "PlayerTeleportCommand.h"
#include "../../../Utils/Utils.h"
#include "../../Module/ModuleManager.h"

PlayerTeleportCommand::PlayerTeleportCommand() : IMCCommand("playertp", "Teleports to players coordinates", "<NameOfThePlayer>") {
}

PlayerTeleportCommand::~PlayerTeleportCommand() {
}

bool PlayerTeleportCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);  // .playertp <player>
	std::string nameOfPlayer = args->at(1);
	assertTrue(!nameOfPlayer.empty());
	std::string nameOfPlayerLower = std::string(nameOfPlayer);
	std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
	nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

	vec3 pos;
	std::string playerName;
	bool gotEntity = false;
	//Loop through all our players and retrieve their information
	g_Data.forEachEntity([&](C_Entity* currentEntity, bool) {
		if (gotEntity) return;
		if (currentEntity == 0) return;
		int entityType = (int)currentEntity->getEntityTypeId();
		if (entityType != 63 && entityType != 319) return;     //skip non player entities
		if (currentEntity == g_Data.getLocalPlayer()) return;  //skip ourself

		std::string name(currentEntity->getNameTag()->getText());
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name.find(nameOfPlayerLower) == std::string::npos) return;

		pos = *currentEntity->getPos();
		playerName = currentEntity->getNameTag()->getText();
		gotEntity = true;
	});
	static auto partner = moduleMgr->getModule<Partner>();
	if (!gotEntity) {
		if (partner->Partnered.selected == 0)
		clientMessageF("[%sSurge%s] %sCouldn't find player: %s!", GOLD, WHITE, RED, nameOfPlayer.c_str());
		else
			clientMessageF("[%sNG%s] %sCouldn't find player: %s!", GOLD, WHITE, RED, nameOfPlayer.c_str());
		return true;
	}
	g_Data.getLocalPlayer()->setPos(pos);
	if (partner->Partnered.selected == 0)
	clientMessageF("[%sSurge%s] %sTeleported to %s", GOLD, WHITE, BLUE, playerName.c_str());
	else
		clientMessageF("[%sNG%s] %sTeleported to %s", GOLD, WHITE, LIGHT_PURPLE, playerName.c_str());
	return true;
}
