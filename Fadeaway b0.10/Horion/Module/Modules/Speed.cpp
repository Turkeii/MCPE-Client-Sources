#include "Speed.h"

Speed::Speed() : IModule(VK_NUMPAD2, Category::MOVEMENT, "Speed up!") {
	registerFloatSetting("speed", &this->speed, 1, 0.1f, 3.f);
	this->registerBoolSetting("V2", &this->v2, this->v2);
}

Speed::~Speed() {
}

const char* Speed::getModuleName() {
	return ("Speed");  // 48 8D 15 ?? ?? ?? ?? 48 8B CB FF 90 ?? ?? ?? ?? 48 8B D8
}

void Speed::onTick(C_GameMode* gm) {
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
	if (v2 == false) {
		float* speedAdr = reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		*speedAdr = speed;
	}

	if (v2 == false && localPlayer->onGround == true && GameData::canUseMoveKeys() && localPlayer->velocity.squaredxzlen() > 0.001f) {
		localPlayer->velocity.x *= 1.39f;
		localPlayer->velocity.z *= 1.39f;
		localPlayer->velocity.y = 0.035f;
	}
}

void Speed::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	float yaw = player->yaw;

	bool pressed = input->forward || input->backward || input->right || input->left;

	if (input->forward && input->backward)
		return;

	if (input->left && input->right && !input->backward)
		return;

	if (input->right) {
		yaw += 90.f;
		if (input->forward)
			yaw -= 45.f;
		else if (input->backward)
			yaw += 45.f;
	}
	if (input->left) {
		yaw -= 90.f;
		if (input->forward)
			yaw += 45.f;
		else if (input->backward)
			yaw -= 45.f;
	}

	if (input->backward && !input->left && !input->right)
		yaw += 180.f;

	if (input->backward && input->left && input->right)
		yaw -= 180.f;

	if (v2 == true) {
		float calcYaw = (yaw + 90) * (PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw)* speed;
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw)* speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}

void Speed::onEnable() {
	if (v2 == false) {
		if (g_Data.getLocalPlayer() == nullptr) {
			this->setEnabled(false);
			return;
		} else {
			origSpeed = *reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84);
		}
	}
}

void Speed::onDisable() {
	if (v2 == false) {
		if (g_Data.getLocalPlayer() != nullptr)
			*reinterpret_cast<float*>(g_Data.getLocalPlayer()->getSpeed() + 0x84) = origSpeed;
	}
}
