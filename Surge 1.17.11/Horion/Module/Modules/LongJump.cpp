#include "LongJump.h"

LongJump::LongJump() : IModule(0, Category::MOVEMENT, "Jump higher than ever before") {
	registerFloatSetting("Jump Height", &this->jumpPower, this->jumpPower, 0.f, 1.f);
	registerFloatSetting("Jump Length", &this->speed, this->speed, 0.f, 10.f);
	//registerBoolSetting("Blink", &this->Blinc, this->Blinc);
	//registerFloatSetting("Blink Frequency", &this->freq, this->freq, 1, 50);
}

LongJump::~LongJump() {
}

const char* LongJump::getModuleName() {
	return ("LongJump");
}

void LongJump::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
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
	moveVec.y = player->velocity.y* jumpPower;
	moveVec.z = moveVec2d.y * speed;
	if (pressed) player->lerpMotion(moveVec);
}

void LongJump::onDisable() {
}