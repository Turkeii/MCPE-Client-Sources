#include "../../../Utils/Utils.h"
#include "PartyCommand.h"

PartyCommand::PartyCommand() : IMCCommand("party", "Party Command", "<name>") {
	registerAlias("p");
}

PartyCommand::~PartyCommand() {
}

bool PartyCommand::execute(std::vector<std::string>* args) {
	assertTrue(g_Data.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);  // .playertp <player>
	std::string nameOfPlayer = args->at(1);
	assertTrue(!nameOfPlayer.empty());
	std::string nameOfPlayerLower = std::string(nameOfPlayer);
	std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
	nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

	C_EntityList* entList = g_Data.getEntityList();
	size_t listSize = entList->getListSize();
	vec3_t pos;

	if (listSize > 5000) {
		return true;
	}
	std::string playerName;
	C_TextPacket textPacket;
	//textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(8)) : message);
	textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
	textPacket.xboxUserId = g_Data.getClientInstance()->minecraftGame->xuid;
	textPacket.messageType = 69;
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
	//Loop through all our players and retrieve their information
	//for (size_t i = 0; i < listSize; i++) {
		//C_Entity* currentEntity = entList->get(i);

		//std::string name(currentEntity->getNameTag()->getText());

		//std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		//if (currentEntity == 0)
			//break;

		//if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
			//continue;

		//if (name.find(nameOfPlayerLower) == std::string::npos)
			//continue;

		//pos = *currentEntity->getPos();
		//playerName = currentEntity->getNameTag()->getText();
		//break;
	//}
	//if (pos.iszero()) {
		//clientMessageF("[%sPacket%s] %sCouldn't find player: %s!", GRAY, WHITE, RED, nameOfPlayer.c_str());
		//return true;
	//}
	g_Data.getLocalPlayer()->setPos(pos);
	clientMessageF("[%sPacket%s] %sSuccessfully Invited %s", GRAY, WHITE, GREEN, playerName.c_str());
	return true;
}