#include "PlayerTPCommand.h"
#include "../../../Utils/Utils.h"
#include "pch.h"

PlayerTPCommand::PlayerTPCommand() : IMCCommand("PlayerTPCommand", "Teleports to players coordinates", "<name>") {
}

bool PlayerTPCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	std::string nameOfPlayer = args->at(1);
	assertTrue(!nameOfPlayer.empty());
	std::string nameOfPlayerLower = std::string(nameOfPlayer);
	std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
	nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

	vec3_t pos;
	std::string playerName;
	bool gotEntity = false;
	//Loop through all our players and retrieve their information
	g_Data.forEachEntity([&](C_Entity* currentEntity, bool) {
		if (gotEntity) return;
		if (currentEntity == 0) return;
		if (currentEntity->getEntityTypeId() != 319) return;
		if (currentEntity == g_Data.getLocalPlayer()) return;

		std::string name(currentEntity->getNameTag()->getText());
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name.find(nameOfPlayerLower) == std::string::npos) return;

		pos = *currentEntity->getPos();
		playerName = currentEntity->getNameTag()->getText();
		gotEntity = true;
	});

	if (!gotEntity) {
		clientMessageF("[Packet] %sCouldn't find player: %s!", RED, nameOfPlayer.c_str());
		return true;
	}

	g_Data.getLocalPlayer()->setPos(pos);
	clientMessageF("[Packet] %sTeleported to %s", GREEN, playerName.c_str());
	return true;
}