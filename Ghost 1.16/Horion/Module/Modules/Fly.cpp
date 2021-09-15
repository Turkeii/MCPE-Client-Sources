#include "Fly.h"

Fly::Fly() : IModule(0, Category::MOVEMENT, "Litturaly just a fly") {
	registerFloatSetting("Speed", &this->speed2, this->speed2, 0.50f, 2.00f);  //allows you to ajust your speed.
}

Fly::~Fly() {
}

const char* Fly::getModuleName() {
	return ("Fly");
}

bool Fly::isFlashMode() {
	return false;
}

void Fly::onEnable() {
}

void Fly::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	if (player == nullptr) return;
	if (player->isSneaking())
		return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (input->right) {
		yaw += 90.f;
		if (input->forward)
			yaw -= 20.f;

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

	float calcYaw = (yaw + 90.f) * (PI / 180.f);
	vec3_t moveVec;
	moveVec.x = cos(calcYaw) * speed2;
	moveVec.y = player->velocity.y;
	moveVec.z = sin(calcYaw) * speed2;
	if (pressed) player->lerpMotion(moveVec);
}

void Fly::onTick(C_GameMode* gm) {
	//keeps you in the air
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.5f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.5f;
	}
	gm->player->velocity.y = glideModEffective;
	auto player = g_Data.getLocalPlayer();
	float yaw = player->yaw;
	player->stepHeight = 1.f;
	
}

void Fly::onDisable() {
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;  //makes sure your timer is noraml (20)
	g_Data.getLocalPlayer()->stepHeight = 0.5625f;         //just leave it like this idk u can remove it
}
