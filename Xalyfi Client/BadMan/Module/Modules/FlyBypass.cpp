#include "FlyBypass.h"

FlyBypass::FlyBypass() : IModule(0, Category::MOVEMENT, "2b2e.org fly bypass") {
}

FlyBypass::~FlyBypass() {
}

const char* FlyBypass::getModuleName() {
	return "FlyBypass";
}

void FlyBypass::onTick(C_GameMode* gm) {
	*g_Data.getClientInstance()->minecraft->timer = 500.f;
	glideModEffective = -0.0001f;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	gm->player->velocity.y = glideModEffective;
	auto player = g_Data.getLocalPlayer();
	if (player->onGround) {
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

		vec3_t pos;
		pos.x = 0.f + pPos.x;
		pos.y = 0.20f + pPos.y;
		pos.z = 0.f + pPos.z;

		g_Data.getLocalPlayer()->setPos(pos);
	}
}

void FlyBypass::onEnable() {  // Only on The Hive
	auto player = g_Data.getLocalPlayer();
	vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;

	vec3_t pos;
	pos.x = 0.f + pPos.x;
	pos.y = 0.20f + pPos.y;
	pos.z = 0.f + pPos.z;

	g_Data.getLocalPlayer()->setPos(pos);
}

void FlyBypass::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}

bool FlyBypass::isFlashMode() {
	return false;
}

void FlyBypass::onMove(C_MoveInputHandler* input) {
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

	float calcYaw = (yaw + 90) * (PI / 180);
	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * 0.36f;
	moveVec.y = player->velocity.y;
	moveVec.z = sin(calcYaw) * 0.36f;
	if (pressed) player->lerpMotion(moveVec);
}