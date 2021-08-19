#include "HiveFlyTwo.h"

HiveFlyTwo::HiveFlyTwo() : IModule(0, Category::MOVEMENT, "Bypassing fly for The Hive. Credit to R9J9") {
}

const char* HiveFlyTwo::getModuleName() {
	return "HiveFly2";
}

void HiveFlyTwo::onTick(C_GameMode* gm) {
	if (gm->player->onGround == true) {
		gm->player->velocity.y = 1;
		gm->player->velocity.x *= 1;
		gm->player->velocity.z *= 1;
	}
	gm->player->velocity.y = -0.0000;
	*g_Data.getClientInstance()->minecraft->timer = 40.f;
	gm->player->setSprinting(true);
}

void HiveFlyTwo::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, (input->sideMovement * -1.f)};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * hivespeed;
	moveVec.z = moveVec2d.y * hivespeed;
	moveVec.y = player->velocity.y;
	if (pressed) player->lerpMotion(moveVec);
}
void HiveFlyTwo::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}