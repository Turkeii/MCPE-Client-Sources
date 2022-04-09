#include "LongJump.h"

#include "../../Module/ModuleManager.h"

LongJump::LongJump() : IModule(0x0, Category::MOVEMENT, "Jump, but Long") {
	registerBoolSetting("Slow", &slow, slow);
	registerBoolSetting("Hit", &hit, hit);
	registerFloatSetting("Height", &height, height, 0.2f, 5.f);
	registerFloatSetting("Speed", &speed, speed, 0.3f, 5.f);
}

const char* LongJump::getModuleName() {
		return "LongJump";
}

void LongJump::onEnable() {
	if (hit && g_Data.getLocalPlayer()->onGround) {
		g_Data.getLocalPlayer()->animateHurt();
	}
	if (slow && g_Data.getLocalPlayer()->onGround) {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(1.5f);
	}
}

void LongJump::onTick(C_GameMode* gm) {
	auto timerMod = moduleMgr->getModule<Timer>();
	if (timerMod->isEnabled()) {
		timerMod->setEnabled(false);
	}
}

void LongJump::onMove(C_MoveInputHandler* input) {
	if (!g_Data.isInGame()) {
		auto hop = moduleMgr->getModule<Bhop>();
		hop->setEnabled(false);
	}
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	if (player->onGround && pressed)
		player->jumpFromGround();
	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3 moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	moveVec.x = moveVec2d.x * speed;
	moveVec.y = height;
	player->velocity.y;
	moveVec.z = moveVec2d.y * speed;
	if (pressed && player->onGround) player->lerpMotion(moveVec);
	auto longjumpMod = moduleMgr->getModule<LongJump>();
	if (longjumpMod->isEnabled()) {
		longjumpMod->setEnabled(false);
	}
	auto bhopMod = moduleMgr->getModule<Bhop>();
	if (bhopMod->isEnabled()) {
		bhopMod->setEnabled(false);
	}
}

void LongJump::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
}