#include "Disabler.h"

Disabler::Disabler() : IModule('0', Category::MISC, "Disabler Helped By Packet") {
	registerBoolSetting("Hive", &this->hive, this->hive);
	registerBoolSetting("Elytra Fly", &this->elytra, this->elytra);
	registerFloatSetting("Fly Speed", &this->speed, this->speed, 0.1f, 10.f);
}

const char* Disabler::getModuleName() {
	return ("Disabler");
}

void Disabler::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (this->elytra && g_Data.isInGame()) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
		C_PlayerActionPacket p;
		p.action = 16;//15
		p.entityRuntimeId = g_Data.getLocalPlayer()->entityRuntimeId;
		g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
}

void Disabler::onMove(C_MoveInputHandler* input) {
	if (this->elytra) {
		auto player = g_Data.getLocalPlayer();
		if (this->elytra && g_Data.isInGame()) {
			if (player == nullptr) return;

			vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
			bool pressed = moveVec2d.magnitude() > 0.00f;

			float calcYaw = (player->yaw + 90) * (PI / 180);
			vec3_t moveVec;
			float c = cos(calcYaw);
			float s = sin(calcYaw);
			moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
			moveVec.x = moveVec2d.x * speed;
			moveVec.y = player->velocity.y = 0;
			moveVec.z = moveVec2d.y * speed;
			if (pressed) player->lerpMotion(moveVec);
		}
		vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;
		if (!pressed) {
			player->velocity.x = 0;
			player->velocity.z = 0;
		}
		if (g_Data.canUseMoveKeys()) {
			if (input->isJumping) {
				player->velocity.y += speed;
			}
			if (input->isSneakDown) {
				player->velocity.y -= speed;
			}
		}
	}
}
void Disabler::onSendPacket(C_Packet* packet) {
}
