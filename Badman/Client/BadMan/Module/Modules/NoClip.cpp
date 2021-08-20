#include "NoClip.h"

NoClip::NoClip() : IModule(0x0, Category::MOVEMENT, "NoClip through walls on all axis") {
	registerFloatSetting("Horizontal Speed", &this->speed, this->speed, 0.1f, 1.f);
	registerFloatSetting("Vertical Speed", &this->upanddown, this->upanddown, 0.1f, 1.f);
	this->registerBoolSetting("Save Old POS", &this->NoPacket, this->NoPacket);
}

NoClip::~NoClip() {
}

const char* NoClip::getModuleName() {
	return ("NoClip");
}

void NoClip::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y - (float)1.8f;
	gm->player->velocity = vec3_t(0, 0, 0);
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += upanddown;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= upanddown;
	}
	gm->player->velocity.y = glideModEffective;
}

void NoClip::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;


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
	moveVec.x = cos(calcYaw) * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = sin(calcYaw) * speed;
	if(pressed) player->lerpMotion(moveVec);
}

void NoClip::onEnable() {
	if (NoPacket)
	if (g_Data.getLocalPlayer() != nullptr) {
		oldPos = *g_Data.getLocalPlayer()->getPos();
	}
}

void NoClip::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->aabb.upper.y = g_Data.getLocalPlayer()->aabb.lower.y + (float)1.8f;
	if (NoPacket)
		g_Data.getLocalPlayer()->setPos(oldPos);
}

