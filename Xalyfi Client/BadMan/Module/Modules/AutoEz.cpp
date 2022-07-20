#include "AutoEz.h"

AutoEz::AutoEz() : IModule(0x0, Category::COMBAT, "XalyfiEZ") {
}

AutoEz::~AutoEz() {
}

const char* AutoEz::getModuleName() {
	return ("AutoEZ");
}

static std::vector<C_Entity*> targetList;
void findEntity995(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 63)  // player
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 7) {
		targetList.push_back(currentEntity);
	}
}

void AutoEz::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (counter == 0)
		RandMessage = "ez";
	else if (counter == 1)
		RandMessage = "ez you are ez so bad";
	
	targetList.clear();

	g_Data.forEachEntity(findEntity995);
	if (!targetList.empty() && g_Data.isInGame()) {
		if (GameData::canUseMoveKeys()) {
			if (counter >= 1) {
				counter = 0;
			} else
				counter++;
			if (targetList[0]->isAlive() && targetList[0]->height > 1.5f && targetList[0]->damageTime > 1) {
				foundPlayer = true;
			}

			if (foundPlayer && !targetList[0]->isAlive() && !targetList[0]->canShowNameTag() && targetList[0]->getDeathTime() >= 0 && targetList[0]->getNameTag()->getTextLength() > 1) {
				isDead = true;
			}

			if (isDead) {
				C_TextPacket textPacket;
				textPacket.message.setText(RandMessage);
				textPacket.sourceName.setText(g_Data.getLocalPlayer()->getNameTag()->getText());
				textPacket.xboxUserId = std::to_string(g_Data.getLocalPlayer()->getUserId());
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
				foundPlayer = false;
				isDead = false;
			}
		}
	}
	if (targetList.empty()) {
		foundPlayer = false;
		isDead = false;
	}
}