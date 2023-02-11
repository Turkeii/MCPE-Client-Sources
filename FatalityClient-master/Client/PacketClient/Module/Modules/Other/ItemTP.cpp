#include "../../ModuleManager.h"
#include "ItemTP.h"
#include "../pch.h"

ItemTP::ItemTP() : IModule(0, Category::OTHER, "Teleports you to items") {
	registerIntSetting("Range", &range, range, 1, 255);
	registerIntSetting("Delay", &delay, delay, 0, 50);
}

const char* ItemTP::getModuleName() {
	return "ItemTP";
}

static std::vector<C_Entity*> targetList;
void findEntityz69(C_Entity* currentEntity, bool isRegularEntity) {
	static auto itemTP = moduleMgr->getModule<ItemTP>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 64)  // item
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < itemTP->range) targetList.push_back(currentEntity);
}

void ItemTP::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	prevPos = *player->getPos();
}

void ItemTP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	C_MovePlayerPacket teleportPacket;
	targetList.clear();
	g_Data.forEachEntity(findEntityz69);
	Odelay++;
	if (!targetList.empty()) {
		if (Odelay >= delay) {
			vec3_t pos = *targetList[0]->getPos();
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
			C_LocalPlayer* player = g_Data.getLocalPlayer();
			player->setPos(vec3_t(pos.x, pos.y + 1.5f, pos.z));
			Odelay = 0;
		}
	} else {
		//auto notification = g_Data.addNotification("ItemTP", "ItemTP: No items in range"); notification->duration = 15;
		player->setPos(prevPos);
		setEnabled(false);
	}
}

void ItemTP::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	player->setPos(prevPos);
}