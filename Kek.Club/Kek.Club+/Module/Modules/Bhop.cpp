#include "Bhop.h"
bool hive = false;
Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerFloatSetting("Speed", &speed, 0.32f, 0.1f, 0.8f);
	registerBoolSetting("Hive", &hive, false);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return ("Bhop");
}

void Bhop::onMove(C_MoveInputHandler* input) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (hive) {
		C_MovePlayerPacket plr(player, *player->getPos());
		plr.pitch += 0.5f;
		plr.yaw += 0.5f;
		plr.headYaw += 0.5f;
		speed = RandomFloat(.33f, .37f) * 0.9;
	}
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (player->onGround && pressed)
		player->jumpFromGround();

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
