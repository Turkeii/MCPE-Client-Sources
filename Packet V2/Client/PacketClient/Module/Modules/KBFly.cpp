#include "KBFly.h"

KBFly::KBFly() : IModule(0, Category::MOVEMENT, "Fly when you take damage") {
	registerBoolSetting("ResetValues", &resetValues, resetValues);
	registerFloatSetting("FlySpeed", &speedMod, speedMod, 0.1f, 4.f);
	registerFloatSetting("StandingY-Vel", &standVel, 0, 0.0f, 2.f);
	registerFloatSetting("MovingY-Vel", &moveVel, 0, 0.0f, 2.f);
	registerBoolSetting("NoVelocity", &stop, stop);
	registerBoolSetting("VanillaFly", &vanf, vanf);
	registerBoolSetting("NoStopFly", &nostop, nostop);
	registerBoolSetting("EnableGold", &turnOnGold, turnOnGold);
}

KBFly::~KBFly() {
}

const char* KBFly::getModuleName() {
	return ("KnockbackFly");
}

void KBFly::onTick(C_GameMode* gm) {
	float calcYaw = (gm->player->yaw + 90) * (PI / 180);
	float calcPitch = (gm->player->pitch) * -(PI / 180);
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (input == nullptr) return;
	auto fuckMod = moduleMgr->getModule<Breaker>();

	if (!fuckMod->gold && turnOnGold)
		fuckMod->gold = true;

	vec3_t moveVec;
	if (resetValues) {
		standVel = 0;
		moveVel = 0;
		speedMod = 1;
	}
	if (stop) gm->player->velocity = vec3_t(0.f, -standVel, 0.f);
	//gm->player->velocity.y = -standVel;
	if (!vanf) {
		if (gm->player->damageTime) {
			moveVec.x = cos(calcYaw) * speedMod;
			moveVec.y = -moveVel;
			moveVec.z = sin(calcYaw) * speedMod;

			gm->player->lerpMotion(moveVec);
		}
	}

	if (vanf && gm->player->damageTime) {
		float yaw = gm->player->yaw;

		if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
			return;
		else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey)) {
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey)) {
			yaw += 180.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 90.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 90.f;
			keyPressed = true;
		}

		if (GameData::isKeyDown(*input->sneakKey) && GameData::isKeyDown(*input->spaceBarKey)) {
			return;
			gm->player->velocity = vec3_t(0, 0, 0);
		} else if (GameData::isKeyDown(*input->spaceBarKey)) {
			vanFYVel = speedMod;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->sneakKey)) {
			vanFYVel = -speedMod;
			keyPressed = true;
		} else if (!GameData::isKeyDown(*input->spaceBarKey) && !GameData::isKeyDown(*input->sneakKey)) {
			vanFYVel = 0.f;
			gm->player->velocity.y = -0.f;
			//keyPressed = true;
		}
		gm->player->velocity = vec3_t(0, 0, 0);
		if (yaw >= 180)
			yaw -= 360.f;

		float calcYaw = (yaw + 90) * (PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = vanFYVel;
		moveVec.z = sin(calcYaw) * speedMod;
		if (keyPressed) {
			gm->player->lerpMotion(moveVec);
			keyPressed = false;
		}
	}
	if (nostop) {
		if (gm->player->damageTime)
			helper = true;
		if (helper && !gm->player->damageTime) {
			vec3_t moveVec;
			moveVec.x = cos(calcYaw) * 0.33f;
			moveVec.y = -0.001f;
			moveVec.z = sin(calcYaw) * 0.33f;
			gm->player->lerpMotion(moveVec);
		}
	}


}

void KBFly::onEnable() {
	helper = false;
}

void KBFly::onDisable() {
	float trueStop = __STDCPP_DEFAULT_NEW_ALIGNMENT__ + _ENABLE_ATOMIC_REF_ALIGNMENT_CHECK + INFINITY - 1 + NULL;
	auto player = g_Data.getLocalPlayer();
	auto fuckMod = moduleMgr->getModule<Breaker>();
	helper = false;
	if (nostop) {
		player->velocity = vec3_t(0.f, -0.4f, 0.f);
		C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
	if (turnOnGold) {
		fuckMod->gold = false;
	}
}
