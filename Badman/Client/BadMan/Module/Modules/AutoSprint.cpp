#include "AutoSprint.h"

AutoSprint::AutoSprint() : IModule(0x0, Category::MOVEMENT, "Automatically sprint without holding the key") {
	registerBoolSetting("all directions", &this->alldirections, this->alldirections);
}

AutoSprint::~AutoSprint() {
}

const char* AutoSprint::getModuleName() {
	return ("AutoSprint");
}

void AutoSprint::onTick(C_GameMode* gm) {
	if (!alldirections) {
		if (!gm->player->isSprinting() && gm->player->velocity.magnitudexz() > 0.01f) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
				gm->player->setSprinting(true);
		}
	}

	if (alldirections) {
		float speed = 0.17f;
		float yaw = gm->player->yaw;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
			gm->player->setSprinting(true);

		if (gm->player->isJumping() == true && gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->onGround == false) {
			speed = 0.30f;
		}

		if (gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->isJumping() == false && gm->player->onGround == false) {
			speed = 0.30f;
		}

		if (gm->player->onGround == false && gm->player->isJumping() == false && gm->player->isInLava() == true) {
			speed = 0.225f;
		}

		if (gm->player->onGround == false && gm->player->isJumping() == false && gm->player->isInWater() == true) {
			speed = 0.225f;
		}

		if (gm->player->isInLava() == true && gm->player->isJumping() == true) {
			speed = 0.225f;
		}

		if (gm->player->isInWater() == true && gm->player->isJumping() == true) {
			speed = 0.225f;
		}

		if (gm->player->onGround && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false) {
			speed = 0.17f;
		}

		if (gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->isJumping() == true && gm->player->onGround == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = 0.13f;
		}

		if (gm->player->onGround == false && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = 0.13f;
		}

		if (gm->player->onGround && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = 0.10f;
		}

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

		float calcYaw = (yaw + 90) * (PI / 180);
		//float calcPitch = (gm->player->pitch) * -(PI / 180);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = gm->player->velocity.y;
		moveVec.z = sin(calcYaw) * speed;
		if (keyPressed) {
			gm->player->lerpMotion(moveVec);
			keyPressed = false;
		}
	}
}