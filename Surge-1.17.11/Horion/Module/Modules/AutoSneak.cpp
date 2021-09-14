#include "AutoSneak.h"

AutoSneak::AutoSneak() : IModule(0, Category::MOVEMENT, "Automatically sneak without holding the key") {
	this->registerBoolSetting("silent", &this->doSilent, doSilent);
}

AutoSneak::~AutoSneak() {
}

const char* AutoSneak::getModuleName() {
	return ("AutoSneak");
}

void AutoSneak::onTick(C_GameMode* gm) {
	if (doSilent) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
	}
	if (!doSilent) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
	}
	if (doSilent) {
		if (g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true) {
			C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

			if (input == nullptr)
				return;

			float speed = 0.325f;
			float yaw = gm->player->yaw;

			if (GameData::isKeyDown(*input->spaceBarKey) && gm->player->onGround)
				gm->player->jumpFromGround();

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
			if (yaw >= 180)
				yaw -= 360.f;

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
}

void AutoSneak::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;

	C_PlayerActionPacket p;
	p.action = 12;  //stop crouch packet
	p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
	g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
}

void AutoSneak::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return; //fixed crash
	if (!doSilent) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
	if (doSilent) {
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
}
