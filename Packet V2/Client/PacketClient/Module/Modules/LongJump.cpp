#include "LongJump.h"

#include "../../Module/ModuleManager.h"

LongJump::LongJump() : IModule(0, Category::MOVEMENT, "JUMP YES") {
	registerBoolSetting("SlowDown", &slowDown, slowDown);
	registerBoolSetting("Damage", &damage, damage);
	registerBoolSetting("Old", &old, old);
	registerFloatSetting("Height", &height, height, 0.2f, 5.f);
	registerFloatSetting("Speed", &speed, speed, 0.5f, 5.f);
}

const char* LongJump::getModuleName() {
	return "LongJump";
}

void LongJump::onEnable() {
	auto player = g_Data.getLocalPlayer();
	counter2 = 0;
	if (damage) {
		player->animateHurt();
	}
	if (slowDown) {
		if (g_Data.canUseMoveKeys()) {
			*g_Data.getClientInstance()->minecraft->timer = 2.f;
			counter = 1;
		}
	} else {
		if (g_Data.canUseMoveKeys())
			*g_Data.getClientInstance()->minecraft->timer = 35.f;
	}
}

void LongJump::onTick(C_GameMode* gm) {
	auto timer = moduleMgr->getModule<Timer>();
	auto speed = moduleMgr->getModule<Speed>();
	auto player = g_Data.getLocalPlayer();
	speed->setEnabled(false);
	timer->setEnabled(false);
	if (slowDown) {
		if (counter == 20) {
			*g_Data.getClientInstance()->minecraft->timer = 20.f;  // prevent bug where you would stay frozen when in menu
			counter = 1;
		} else {
			counter++;
		}
	}
	if (old) {
		if (strcmp(g_Data.getRakNetInstance()->serverIp.getText(), "geo.hivebedrock.network") == 0)
			if (!player->onGround)
				setEnabled(false);
	} else {
		if (!gm->player->onGround)
			counter2++;
	}
}

void LongJump::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	vec2_t moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	vec3_t moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
	if (old) {
		if (player->onGround && pressed)
			player->jumpFromGround();
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = height;
		player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
		setEnabled(false);
	} else {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
		if (player->onGround && pressed) {
			player->jumpFromGround();
			player->velocity.y = height;
		}
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);

		if (counter2 >= 3 && player->onGround) {
			counter2 = 0;
			setEnabled(false);
			player->velocity = vec3_t(0, 0, 0);
		}
	}
}

void LongJump::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	counter2 = 0;
}