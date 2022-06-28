#include "Jetpack.h"

#include "../../../Utils/Logger.h"

Jetpack::Jetpack() : IModule('F', Category::MOVEMENT, "Fly around like you had a Jetpack!") {
	registerFloatSetting("speed", &speedMod, 1, 0.2f, 5.f);
	registerBoolSetting("Bypass", &isBypass, isBypass);
}

Jetpack::~Jetpack() {
}

bool Jetpack::isFlashMode() {
	return true;
}

const char* Jetpack::getModuleName() {
	return ("Jetpack");
}

void Jetpack::onLevelRender() {
	float calcYaw = (g_Data.getCGameMode()->player->yaw + 90) * (PI / 180);
	float calcPitch = (g_Data.getCGameMode()->player->pitch) * -(PI / 180);

	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
		moveVec.y = sin(calcPitch) * speedMod;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

		g_Data.getCGameMode()->player->lerpMotion(moveVec);
	} else {
		delay++;

		if (delay >= 5) {
			vec3_t pos = *g_Data.getLocalPlayer()->getPos();
			C_MovePlayerPacket a(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y += 0.35f;
			a = C_MovePlayerPacket(g_Data.getLocalPlayer(), pos);
			g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&a);

			g_Data.getCGameMode()->player->velocity.y = 0.465f;
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * speedMod;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * speedMod;

			g_Data.getCGameMode()->player->velocity.x = moveVec.x;
			g_Data.getCGameMode()->player->velocity.z = moveVec.z;

			float teleportX = cos(calcYaw) * cos(calcPitch) * 0.00000005f;
			float teleportZ = sin(calcYaw) * cos(calcPitch) * 0.00000005f;

			pos = *g_Data.getCGameMode()->player->getPos();
			g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y - 0.15f, pos.z + teleportZ));

			g_Data.getCGameMode()->player->velocity.y -= 0.15f;
			delay = 0;
		}
	}
}