#include "Bhop.h"

Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerBoolSetting("Timer", &this->timer, this->timer);
	registerBoolSetting("LowHop", &this->LowHop, this->LowHop);
	registerBoolSetting("Speed", &this->bhopspeed, this->bhopspeed);
	registerFloatSetting("LowHop Frequency", &this->hight, this->hight, 0.1f, 1.f);
	registerFloatSetting("Bhop Speed", &this->speed, this->speed, 0.1f, 0.8f);
	registerFloatSetting("Timer Speed", &this->tspeed, this->tspeed, 0.21f, 2.f);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return ("Bhop");
}

void Bhop::onMove(C_MoveInputHandler* input) {
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

	if (counter == 1) {
		if (pressed && LowHop) {
			player->velocity.y += -hight;
		}
	}

	if (counter == 2) {
		counter = 0;
	} else {
		counter++;
	}
	
	
	if (pressed && bhopspeed) {
		player->velocity.y = -0.5f;
	}

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = moveVec2d.y * speed;
	if(pressed) player->lerpMotion(moveVec);
}

void Bhop::onTick(C_GameMode* gm) {
	auto stepMod = moduleMgr->getModule<Step>();
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	if (!g_Data.canUseMoveKeys())
		return;
	if (this->timer) {
		*g_Data.getClientInstance()->minecraft->timer = 72.f * tspeed;
	}
}

void Bhop::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}
