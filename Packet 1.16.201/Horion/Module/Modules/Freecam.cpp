#include "../../Module/ModuleManager.h"
#include "Freecam.h"

Freecam::Freecam() : IModule(0, Category::MISC, "burn") {
	registerFloatSetting("Speed", &this->speed, this->speed, 0.5f, 3.f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return ("Freecam");
}

void Freecam::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (g_Data.getLocalPlayer() != nullptr) {
		oldPos = *g_Data.getLocalPlayer()->getPos();
	}
}

bool Freecam::isFlashMode() {
	return false;
}

void Freecam::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	gm->player->fallDistance = 0.f;
	gm->player->aabb.upper.y = 0.f;
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) {
		gm->player->velocity = vec3_t(0, 0, 0);
	}
	if (counter == 5) {
		counter = 0;
	} else {
		counter++;
	}
	if (counter == 1) {
		player->velocity.y = speed2;
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
	auto bhopMod = moduleMgr->getModule<Bhop>();
	if (bhopMod->isEnabled()) {
		bhopMod->setEnabled(false);
	}
}

void Freecam::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (input->isJumping) {
		player->velocity.y += speed;
		player->fallDistance = 0.f;
	}
	if (input->isSneakDown) {
		player->velocity.y -= speed;
		player->fallDistance = 0.f;
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

void Freecam::onDisable() {
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	if (!player->onGround) {
		player->velocity.x = 0.f;
		player->velocity.y = 0.f;
		player->velocity.z = 0.f;
	}
	if (g_Data.getLocalPlayer() != nullptr) {
		g_Data.getLocalPlayer()->setPos(oldPos);
	}
}