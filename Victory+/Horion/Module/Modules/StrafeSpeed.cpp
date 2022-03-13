#include "StrafeSpeed.h"

StrafeSpeed::StrafeSpeed() : IModule(0x0, Category::MOVEMENT, "Strafe!!!!") {
	registerBoolSetting("Sprinting", &this->sprint, this->sprint);

	registerFloatSetting("GroundSpeed", &this->nspeed, this->nspeed, 0.3, 1);
	registerFloatSetting("AirSpeed", &this->jspeed, this->jspeed, 0.17, 1);
	registerFloatSetting("LavaSpeed", &this->lspeed, this->lspeed, 0.225, 1);
	registerFloatSetting("WaterSpeed", &this->wspeed, this->wspeed, 0.225, 1);
	registerFloatSetting("AirSneakedSpeed", &this->jsspeed, this->jsspeed, 0.13, 1);
	registerFloatSetting("SneakedSpeed", &this->sspeed, this->sspeed, 0.1, 1);
}

StrafeSpeed::~StrafeSpeed() {
}

const char* StrafeSpeed::getModuleName() {
	return ("StrafeSpeed");
}

void StrafeSpeed::onTick(C_GameMode* gm) {
		float speed = 0.17f;
		float yaw = gm->player->yaw;
		C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		if (sprint) {
			gm->player->setSprinting(true);
		}
		if (gm->player->isJumping() == true && gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->onGround == false) {
			speed = nspeed;
		}

		if (gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->isJumping() == false && gm->player->onGround == false) {
			speed = jspeed;
		}

		if (gm->player->onGround == false && gm->player->isJumping() == false && gm->player->isInLava() == true) {
			speed = lspeed;
		}

		if (gm->player->onGround == false && gm->player->isJumping() == false && gm->player->isInWater() == true) {
			speed = wspeed;
		}

		if (gm->player->isInLava() == true && gm->player->isJumping() == true) {
			speed = lspeed;
		}

		if (gm->player->isInWater() == true && gm->player->isJumping() == true) {
			speed = wspeed;
		}

		if (gm->player->onGround && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false) {
			speed = nspeed;
		}

		if (gm->player->isInLava() == false && gm->player->isInWater() == false && gm->player->isJumping() == true && gm->player->onGround == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = jsspeed;
		}

		if (gm->player->onGround == false && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = sspeed;
		}

		if (gm->player->onGround && gm->player->isInWater() == false && gm->player->isInLava() == false && gm->player->isJumping() == false && GameData::isKeyDown(VK_SHIFT)) {
			speed = jsspeed;
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
