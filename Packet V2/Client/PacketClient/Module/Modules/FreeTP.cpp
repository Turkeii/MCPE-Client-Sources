#include "FreeTP.h"

#include "../../Module/ModuleManager.h"

FreeTP::FreeTP() : IModule(0, Category::EXPLOIT, "weee") {
	registerFloatSetting("Speed", &speed, speed, 0.5f, 3.f);
}

FreeTP::~FreeTP() {
}

const char* FreeTP::getModuleName() {
	return ("FreeTP");
}

void FreeTP::onEnable() {
	auto speed = moduleMgr->getModule<Speed>();
	if (speed->isEnabled())
		speedWasEnabled = true;
}

void FreeTP::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	gm->player->fallDistance = 0.f;
	gm->player->aabb.upper.y = 0.f;
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (input->forwardKey && input->backKey && input->rightKey && input->leftKey)
		gm->player->velocity = vec3_t(0, 0, 0);
	player->velocity.y = -0.f;
	auto speed = moduleMgr->getModule<Speed>();
	auto flight = moduleMgr->getModule<Flight>();
	speed->setEnabled(false);
}

void FreeTP::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (input->isJumping) {
		player->velocity.y += speed;
		player->fallDistance = -0.1f;
	}
	if (input->isSneakDown) {
		player->velocity.y -= speed;
		player->fallDistance = -0.1f;
	}
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
	if (pressed) {
		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}

void FreeTP::onDisable() {
	auto player = g_Data.getLocalPlayer();
	player->velocity = vec3_t(0, 0, 0);
	if (g_Data.getLocalPlayer() != nullptr) {
		g_Data.getLocalPlayer()->aabb.upper.y += 1.8f;
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;
		vec3_t pos;
		pos.x = pPos.x;
		pos.y = 0.0000001f + pPos.y;
		pos.z = pPos.z;
		g_Data.getLocalPlayer()->setPos(pos);
	}
	auto speed = moduleMgr->getModule<Speed>();
	if (speedWasEnabled == true) {
		speed->setEnabled(true);
		speedWasEnabled = false;
	}
}