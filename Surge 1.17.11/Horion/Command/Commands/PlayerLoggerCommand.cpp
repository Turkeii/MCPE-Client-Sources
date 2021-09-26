#include "../../../Utils/Utils.h"
#include "PlayerLoggerCommand.h"

PlayerLoggerCommand::PlayerLoggerCommand() : IMCCommand("log", "Logs players coordinates", "") {
}

PlayerLoggerCommand::~PlayerLoggerCommand() {
}

bool PlayerLoggerCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);

	C_EntityList* entList = g_Data.getEntityList();
	size_t listSize = entList->getListSize();

	if (listSize > 5000) {
		return true;
	}
	std::string playerName;
	//Loop through all our players and retrieve their information
	for (size_t i = 0; i < listSize; i++) {
		C_Entity* currentEntity = entList->get(i);

		std::string name(currentEntity->getNameTag()->getText());

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
			continue;

		vec3_t* pos = currentEntity->getPos();
		float yPos = pos->y - 1.62f;
		clientMessageF("[%sSurge%s] %sX: %.2f Y: %.2f Z: %.2f", BLUE, WHITE, BLUE, pos->x, yPos, pos->z);
		clientMessageF("[%sSurge%s] %sLogged %s", BLUE, WHITE, BLUE, playerName.c_str());
		playerName = currentEntity->getNameTag()->getText();
	}
	if (size_t i = 1; i > listSize) {
		clientMessageF("[%sSurge%s] %sCouldn't find player: %s!", BLUE, WHITE, RED, playerName.c_str());
		return true;
	}
	return true;
}