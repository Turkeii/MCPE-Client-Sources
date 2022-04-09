#include "../ModuleManager.h"
#include "ItemTP.h"

ItemTP::ItemTP() : IModule(0, Category::MISC, "Teleports you to items") {
	registerIntSetting("Range", &range, range, 1, 255);
	registerIntSetting("Delay", &delay, delay, 0, 50);
}

const char* ItemTP::getModuleName() {
	return "ItemTP";
}

static std::vector<C_Entity*> targetListz69;

void findEntityz69(C_Entity* currentEntity, bool isRegularEntity) {
	static auto itemTP = moduleMgr->getModule<ItemTP>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity->getEntityTypeId() != 64)  // item
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < itemTP->range) {
		targetListz69.push_back(currentEntity);
	}
}

void ItemTP::onEnable() {
	auto player = g_Data.getLocalPlayer();
	prevPos = *player->getPos();
}

void ItemTP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	C_MovePlayerPacket teleportPacket;
	targetListz69.clear();
	g_Data.forEachEntity(findEntityz69);
	Odelay++;
	if (!targetListz69.empty() && Odelay >= delay) {
		vec3_t pos = *targetListz69[0]->getPos();
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->setPos(vec3_t(pos.x, pos.y + 1.5f, pos.z));
		Odelay = 0;
	}
	if (targetListz69.empty()) {
		auto box = g_Data.addNotification("what", "ItemTP: No items in range");
		box->duration = 15;
		player->setPos(prevPos);
		setEnabled(false);
	}
}

void ItemTP::onDisable() {
	auto player = g_Data.getLocalPlayer();
	player->setPos(prevPos);
}