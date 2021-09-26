#include "Freecam.h"

Freecam::Freecam() : IModule('0', Category::MISC, "Freecam Made By NRG") {
	registerFloatSetting("Speed", &this->speed, this->speed, 0.1f, 1.f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}

void Freecam::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	gm->player->fallDistance = 0.f;
	gm->player->aabb.upper.y = 0.f;  // vertical
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += speed;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= speed;
	}
	gm->player->velocity.y = glideModEffective;
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

//By NRG