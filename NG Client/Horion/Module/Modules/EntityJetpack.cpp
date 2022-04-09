#include "EntityJetpack.h"

#include "../../../Utils/Logger.h"

EntityJetpack::EntityJetpack() : IModule(0x0, Category::ENTITY, "Use the jetpack module while on entities") {
	registerFloatSetting("speed", &speedMod, 1, 0.2f, 3.f);
	registerBoolSetting("Bypass", &isBypass, isBypass);
}

EntityJetpack::~EntityJetpack() {
}

bool EntityJetpack::isFlashMode() {
	return true;
}

const char* EntityJetpack::getModuleName() {
	return ("EntityJetpack");
}
static std::vector<C_Entity*> targetDad;
void findDad(C_Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*g_Data.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetDad.push_back(currentEntity);
	}
}
void EntityJetpack::onTick(C_GameMode* gm) {
	targetDad.clear();
	g_Data.forEachEntity(findDad);

	if (!targetDad.empty()) {
		auto player = targetDad[0];
		float calcYaw = (player->yaw + 90) * (PI / 180);
		float calcPitch = (player->pitch) * -(PI / 180);

		if (!isBypass) {
			vec3 moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.y = sin(calcPitch) * speedMod;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			player->lerpMotion(moveVec);
		} else {
			delay++;

			if (delay >= 5) {
				vec3 pos = *g_Data.getLocalPlayer()->getPos();
				C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
				pos.y += 0.35f;
				a = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
				g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);

				player->velocity.y = 0.465f;
				vec3 moveVec;
				moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
				moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

				player->velocity.x = moveVec.x;
				player->velocity.z = moveVec.z;

				float teleportX = cos(calcYaw) * cos(calcPitch) * 0.00000005f;
				float teleportZ = sin(calcYaw) * cos(calcPitch) * 0.00000005f;

				pos = *player->getPos();
				g_Data.getLocalPlayer()->setPos(vec3(pos.x + teleportX, pos.y - 0.15f, pos.z + teleportZ));

				player->velocity.y -= 0.15f;
				delay = 0;
			}
		}
	}
}