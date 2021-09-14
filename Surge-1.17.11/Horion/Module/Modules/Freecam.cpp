#include "Freecam.h"

Freecam::Freecam() : IModule('0', Category::MISC, "Freecam Made Helped Origionaly By Packet") {
	registerFloatSetting("Speed", &this->speed, this->speed, 0.1f, 10.f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}

void Freecam::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	gm->player->velocity.y = 0;
	gm->player->aabb.upper.y = 0.f;
}

void Freecam::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = moveVec2d.y * speed;
	if (pressed) player->lerpMotion(moveVec);
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

void Freecam::onEnable() {
	if (g_Data.getLocalPlayer() != nullptr) {
		oldPos = *g_Data.getLocalPlayer()->getPos();
	}
}

void Freecam::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr) {
		g_Data.getLocalPlayer()->setPos(oldPos);
	}
	auto player = g_Data.getLocalPlayer();
	if (!player->onGround) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.f;
		player->velocity.z = 0.f;
	}
}