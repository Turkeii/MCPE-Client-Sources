#include "LongJump.h"

LongJump::LongJump() : IModule(0x0, Category::MOVEMENT, "Jump farther and higher") {
	registerFloatSetting("speed", &this->speedMod, 1, 0.7f, 1.5f);
	registerFloatSetting("up", &this->upvel, 1, 0.0285f, 1.f);
}

LongJump::~LongJump() {
}

const char* LongJump::getModuleName() {
	return ("LongJump");
}
void LongJump::onEnable() {
	if (counter <= 500) {
		counter = 0;
	}
	disable = true;
}
void LongJump::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	float yaw = player->yaw;
	auto jumpy = moduleMgr->getModule<LongJump>();
	if (counter >= 500) {
		counter = 499;
	}
	if (player->onGround) {
		counter = 0;
	} else if (!player->onGround) {
		counter++;
	}
	if (player->onGround && disable == true) {  //start up
		player->jumpFromGround();
	}
	if (counter <= 100) {  // in air up
		player->velocity.y += upvel;
	}
	if (!player->onGround && counter <= 100) {  //big boy move
		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		player->setSprinting(true);
		vec3_t moveVec;
		moveVec.x = cos(calcYaw) * speedMod;
		moveVec.y = player->velocity.y;
		moveVec.z = sin(calcYaw) * speedMod;
		disable = false;
		player->lerpMotion(moveVec);
	}
	if (player->onGround && disable == false) {  //auto disable
		jumpy->setEnabled(false);
		player->velocity.x = 0.f;
		player->velocity.z = 0.f;
	}
}
void LongJump::onDisable() {
	auto player = g_Data.getLocalPlayer();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	player->stepHeight = 0.625f;
	if (!player->onGround) {
		player->velocity.x = 0.f;
		player->velocity.z = 0.f;
	}
}