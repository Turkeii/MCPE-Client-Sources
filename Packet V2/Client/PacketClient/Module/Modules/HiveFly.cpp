#include "HiveFly.h"

#include "../../Module/ModuleManager.h"

HiveFly::HiveFly() : IModule(0, Category::MOVEMENT, "Turkey go falling off cliff wee!1!1!!") {
	registerBoolSetting("Boost", &boostMode, boostMode);
	registerFloatSetting("Value", &value, value, -0.5f, 0.5f);
	registerFloatSetting("Speed", &speedA, speedA, 0.10f, 1.f);
}

HiveFly::~HiveFly() {
}

const char* HiveFly::getModuleName() {
	return "HiveFly";
}

void HiveFly::onEnable() {
	auto scaffoldMod = moduleMgr->getModule<Scaffold>();
	auto speedMod = moduleMgr->getModule<Speed>();
	auto player = g_Data.getLocalPlayer();
	scaffoldMod->setEnabled(false);
	speedMod->setEnabled(false);
	if (boostMode) {
		player->animateHurt();
		boostCounter = 1;
	}

	auto scaffold = moduleMgr->getModule<Scaffold>();
	auto speed = moduleMgr->getModule<Speed>();
	if (speed->isEnabled())
		speedWasEnabled = true;
	if (scaffold->isEnabled())
		scfWasEnabled = true;
}

void HiveFly::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	auto scaffoldMod = moduleMgr->getModule<Scaffold>();
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto speedMod = moduleMgr->getModule<Speed>();
	auto player = g_Data.getLocalPlayer();
	scaffoldMod->setEnabled(false);
	speedMod->setEnabled(false);
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	if (boostMode) {
		if (boostCounter == INFINITY) {
			boostCounter = 1;
		} else {
			boostCounter++;
		}
		if (boostCounter == 2) {
			*g_Data.getClientInstance()->minecraft->timer = 1.f;
			value = 0;
			speedA = 1.f;
		}
		if (boostCounter == 4) {
			*g_Data.getClientInstance()->minecraft->timer = 30.f;
			speedA = 0.75f;
		}
		if (boostCounter == 7) {
			*g_Data.getClientInstance()->minecraft->timer = 1.f;
			speedA = 0.60f;
		}
		if (boostCounter == 10) {
			*g_Data.getClientInstance()->minecraft->timer = 5.f;
			value = -0.00;
			speedA = 0.55f;
		}
		if (boostCounter == 13) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;
			value = 0.2;
			speedA = 0.50f;
		}
		if (boostCounter == 16) {
			value = -0.04;
			speedA = 0.48f;
		}
		if (boostCounter == 20) {
			speedA = 0.45f;
			value = -0.03;
		}
		if (boostCounter == 35) {
			speedA = 0.32f;
			value = -0.09;
		}
		if (boostCounter == 50) {
			*g_Data.getClientInstance()->minecraft->timer = 1.f;
		}
	}
	if (counter == 10) {
		counter = 1;
	} else {
		counter++;
	}
	if (counter >= 0) {
		gm->player->velocity = vec3_t(0, 0, 0);
	}
	if (counter <= 2) {
		player->velocity.y = value;
	}
}

void HiveFly::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (boostMode) {
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;
		if (player->onGround && pressed)
			player->jumpFromGround();
	}
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (input->isJumping && counter == 3) {
		player->velocity.y -= 0.000000000001f;
		player->fallDistance = -0.1f;
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

		vec3_t pos;
		pos.x = 0.f + pPos.x;
		pos.y = 4.f + pPos.y;
		pos.z = 0.f + pPos.z;

		g_Data.getLocalPlayer()->setPos(pos);
		*g_Data.getClientInstance()->minecraft->timer = 3.f;
	}
	if (input->isSneakDown && counter == 3) {
		player->velocity.y -= 0.000000000001f;
		player->fallDistance = -0.1f;
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

		vec3_t pos;
		pos.x = 0.f + pPos.x;
		pos.y = -4.f + pPos.y;
		pos.z = 0.f + pPos.z;

		g_Data.getLocalPlayer()->setPos(pos);
		*g_Data.getClientInstance()->minecraft->timer = 3.f;
	}

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speedA;
	moveVec.y = player->velocity.y;
	moveVec.z = moveVec2d.y * speedA;
	if (pressed) player->lerpMotion(moveVec);
}

void HiveFly::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	auto player = g_Data.getLocalPlayer();
	if (!player->onGround) {
		player->velocity.x = 0.f;
		player->velocity.z = 0.f;
	}

	auto scaffold = moduleMgr->getModule<Scaffold>();
	auto speed = moduleMgr->getModule<Speed>();
	if (speedWasEnabled == true) {
		speed->setEnabled(true);
		speedWasEnabled = false;
	}
	if (scfWasEnabled == true) {
		scaffold->setEnabled(true);
		scfWasEnabled = false;
	}
}