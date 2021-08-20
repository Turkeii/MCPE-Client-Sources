#include "MineplexFly.h"

MineplexFly::MineplexFly() : IModule('R', Category::MOVEMENT, "Flight bypass for Mineplex") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.3f, 2.5f);
	registerFloatSetting("Y-Start", &this->yUp, 1, 0.0f, 1.f);
	this->registerBoolSetting("Up", &this->isBypass, this->isBypass);
}

MineplexFly::~MineplexFly() {
}

bool MineplexFly::isFlashMode() {
	return true;
}

void MineplexFly::onDisable() {
	vec3_t pos = *g_Data.getLocalPlayer()->getPos();
	g_Data.getLocalPlayer()->setPos((pos, pos, pos));
	g_Data.getLocalPlayer()->velocity = vec3_t(0, 0, 0);
}

void MineplexFly::onEnable() {
		vec3_t moveVec;
		float calcYaw = (g_Data.getLocalPlayer()->yaw + 90) * (PI / 180);
		float calcPitch = (g_Data.getLocalPlayer()->pitch) * -(PI / 180);
		float teleportX = cos(calcYaw) * cos(calcPitch) * -0.0f;
		float teleportZ = sin(calcYaw) * cos(calcPitch) * -0.0f;
		moveVec.y = +yUp;
		vec3_t pos = *g_Data.getLocalPlayer()->getPos();
		g_Data.getLocalPlayer()->setPos(vec3_t(pos.x + teleportX, pos.y + yUp, pos.z + teleportZ));
	}

const char* MineplexFly::getModuleName() {
	return ("MineplexFly");
}

void MineplexFly::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);

	if (!isBypass) {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = -0.0 * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	} else {
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = +0.007 * speedMod;
		moveVec.z = sin(calcYaw) * speedMod;

		gm->player->lerpMotion(moveVec);
	}
}
