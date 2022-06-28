#include "AutoEZ.h"

AutoEZ::AutoEZ() : IModule(0x0, Category::MISC, "lets people know ur clouted") {
}

AutoEZ::~AutoEZ() {
}
const char* AutoEZ::getModuleName() {
	return ("AutoEZ");
}
static std::vector<C_Entity*> targetList;
void Dead(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;
	if (currentEntity == g_Data.getLocalPlayer())
		return;
	if (currentEntity->getEntityTypeId() != 63)
		return;
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 7) {
		targetList.push_back(currentEntity);
	}
}
void AutoEZ::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

		wp2 =  "you just got nae nae'd by Kek.Club+";


	targetList.clear();

	g_Data.forEachEntity(Dead);
	if (!targetList.empty() && g_Data.isInGame()) {
		if (GameData::canUseMoveKeys()) {
			if (targetList[0]->isAlive() && targetList[0]->height > 1.5f && targetList[0]->damageTime > 1) {
				foundPlayer = true;
			}

			if (foundPlayer && !targetList[0]->isAlive() && !targetList[0]->canShowNameTag() && targetList[0]->getDeathTime() >= 0 && targetList[0]->getNameTag()->getTextLength() > 1) {
				isDead = true;
			}

			if (isDead) {
				C_TextPacket textPacket;
				textPacket.message.setText(wp2);
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
