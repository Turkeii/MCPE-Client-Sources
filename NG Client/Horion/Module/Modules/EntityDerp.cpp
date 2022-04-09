#include "EntityDerp.h"

EntityDerp::EntityDerp() : IModule(0x0, Category::ENTITY, "Make plays have a seizure irl") {
	registerBoolSetting("theyhaveastroke", &epicStroke, epicStroke);
}

EntityDerp::~EntityDerp() {
}

const char* EntityDerp::getModuleName() {
	return "EntityDerp";
}
static std::vector<C_Entity*> targetBoy;
void findBoy(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == g_Data.getLocalPlayer())  // Skip Local player
		return;

	if (!g_Data.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!g_Data.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 319) {
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}
	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());
	if (dist < 25) {
		targetBoy.push_back(currentEntity);
	}
}
void EntityDerp::onTick(C_GameMode* gm) {
	targetBoy.clear();
	g_Data.forEachEntity(findBoy);

	if (!targetBoy.empty()) {
		auto player = targetBoy[0];
		if (packetMode) {
			C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
			if (epicStroke) {
				p.pitch = (float)(rand() % 360);
				p.yaw = (float)(rand() % 360);
			} else {
				p.pitch = (float)(counter % 360);
				p.yaw = (float)(counter % 360);
			}
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		} else {
			if (epicStroke) {
				player->pitch = (float)(rand() % 360);
				player->bodyYaw = (float)(rand() % 360);
			} else {
				player->pitch = (float)(counter % 360);
				player->bodyYaw = (float)(counter % 360);
			}
		}

		if (counter < 360)
			counter++;
		else
			counter = 0;
	}
}