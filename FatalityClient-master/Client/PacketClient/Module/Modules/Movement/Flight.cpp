#include "Flight.h"
#include "../pch.h"
#include <cmath>

uintptr_t ViewBobbing = FindSignature("0F B6 80 DB 01 00 00");

using namespace std;
Flight::Flight() : IModule(0, Category::MOVEMENT, "Allows you to fly") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("(Motion)", 0);
	mode.addEntry("(Airwalk)", 1);
	mode.addEntry("(Jetpack)", 2);
	mode.addEntry("(Jump)", 3);
	mode.addEntry("(Hive)", 4);
	//mode.addEntry("(Cubecraft)", 5);
	mode.addEntry("(Test)", 6);
	registerBoolSetting("ViewBobbing", &viewBobbing, viewBobbing);
	registerBoolSetting("Damage", &damage, damage);
	registerBoolSetting("Boost", &boost, boost);
	registerFloatSetting("Duration", &duration, duration, 0.5f, 1.05f);
	registerFloatSetting("Speed", &speed, speed, 0.2f, 5.f);
	registerFloatSetting("value", &value, value, -0.15f, 0.00f);
}

const char* Flight::getRawModuleName() {
	return "Fly";
}

const char* Flight::getModuleName() {
	name = string("Fly ") + string(GRAY) + mode.GetEntry(mode.getSelectedValue()).GetName();
	return name.c_str();
}

float hiveSpeedArray[15] = {
0.910000,
0.615559,
0.583347,
0.554032,
0.527356,
0.503081,
0.480991,
0.460887,
0.442595,
0.425948,
0.410799,
0.397015,
0.384470,
0.373055,
0.362665
};

float hiveSafeSpeedArray[12] = {
0.40000,
0.38000,
0.36000,
0.34000,
0.32000,
0.30000,
0.29000,
0.28000,
0.26000,
0.24000,
0.22000,
0.20347
};

void Flight::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	// Variables
	auto speedMod = moduleMgr->getModule<Speed>();
	auto blinkMod = moduleMgr->getModule<Blink>();
	if (speedMod->isEnabled()) speedWasEnabled = true;
	PointingStruct* level = player->pointingStruct;
	vec3_t pos2 = *player->getPos();
	vec3_t* pos = player->getPos();
	viewBobbingEffective = false;
	tick = 0;

	if (damage) { level->playSound("game.player.hurt", *pos, 1, 1); player->animateHurt(); }
	if (boost) speedDuration = speed;

	switch (mode.getSelectedValue()) {
	case 3: // Jump
		enabledHeight = (int)floorf(pos->y);
		break;
	case 4: // Hive
		enabledTick++;
		player->jumpFromGround();
		if (enabledTick >= 1) {
			//pos2.y += 0.1f;
			//player->setPos(pos2);
		}
		break;
	case 6: // Test
		testfloat = speed;
		timerVariable = 5;
		g_Data.getClientInstance()->minecraft->setTimerSpeed(timerVariable);
		blinkMod->setEnabled(true);
		break;
	}
}

bool Flight::isHoldMode() {
	return mode.getSelectedValue() == 2;
}

void Flight::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	tick++;

	// Math
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (mode.getSelectedValue() != 5)
		g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;

	auto targetStrafe = moduleMgr->getModule<TargetStrafe>();
	auto speedMod = moduleMgr->getModule<Speed>();
	auto blinkMod = moduleMgr->getModule<Blink>();
	auto blink = moduleMgr->getModule<Blink>();

	float yaw = player->yaw; float pitch = player->pitch;
	float velocity = g_Data.getLocalPlayer()->velocity.magnitude();
	float velocityxz = g_Data.getLocalPlayer()->velocity.magnitudexz();
	float velocityxy = g_Data.getLocalPlayer()->velocity.magnitudexy();
	bool jumping = GameData::isKeyDown(*input->spaceBarKey);
	bool sneaking = GameData::isKeyDown(*input->sneakKey);
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	float calcYaw = (yaw + 90) * (PI / 180);
	float calcPitch = (pitch) * -(PI / 180);
	vec3_t moveVec;

	if (speedMod->isEnabled()) {
		//auto notification = g_Data.addNotification("Flight:", "Disabled Speed"); notification->duration = 5;
		speedMod->setEnabled(false);
	}

	// Vanilla
	if (mode.getSelectedValue() == 0) {
		if (g_Data.canUseMoveKeys()) {
			if (jumping && targetStrafe->targetListEmpty)
				effectiveValue += currSpeed;
			if (sneaking)
				effectiveValue -= currSpeed;
		}
		if (input->forwardKey && input->backKey && input->rightKey && input->leftKey) MoveUtil::fullStop(false);
		gm->player->velocity.y = effectiveValue;
		effectiveValue = value;
	}

	// Airwalk
	if (mode.getSelectedValue() == 1) {
		if (speedMod->isEnabled() || jumping) player->onGround = false;
		else player->onGround = true;
		gm->player->velocity.y = effectiveValue;
		effectiveValue = value;
	}

	// Jetpack
	if (mode.getSelectedValue() == 2) {
		moveVec.x = cos(calcYaw) * cos(calcPitch) * currSpeed;
		moveVec.y = sin(calcPitch) * currSpeed;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * currSpeed;
		gm->player->lerpMotion(moveVec);
	}

	// Jump
	if (mode.getSelectedValue() == 3) {
		currHeight = (int)floorf(pos->y);

		jumpTick++;
		if (jumpTick >= 8) {
			if (jumping) { enabledHeight == currHeight; enabledHeight += 1; }
			if (sneaking) enabledHeight = 0;
			jumpTick = 0;
		}

		if (hasJumped && !sneaking) tick = 0;
		if (tick >= 15 && !hasJumped && !sneaking) {
			//auto notification = g_Data.addNotification("Flight:", "Reset jump height!");
			//notification->duration = 3;
			enabledHeight = currHeight;
		}

		if (currHeight == enabledHeight) {
			if (velocityxz <= 0.05 && !jumping && !sneaking || !g_Data.canUseMoveKeys()) { player->velocity.y = 0.f; player->onGround = true; }
			else player->jumpFromGround();
			hasJumped = true;
		}
		else hasJumped = false;
	}

	// Hive
	if (mode.getSelectedValue() == 4) { player->setSprinting(true); hiveTick++; }

	// Test
	if (mode.getSelectedValue() == 6) {
		if (g_Data.canUseMoveKeys()) {
			g_Data.getClientInstance()->minecraft->setTimerSpeed(timerVariable);
			if (testfloat > 0.2f) testfloat -= 0.015f;
			if (timerVariable < 21) timerVariable++;
			if (TimerUtil::hasTimedElapsed(100, true)) {
				player->setPos(vec3_t(pos->x, pos->y - 1.f, pos->z));
				timerVariable = 5;
			}
			if (TimerUtil::hasTimedElapsed(50, false)) blinkMod->setEnabled(false);
		}
	}
}

void Flight::onPlayerTick(C_Player* plr) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
}

void Flight::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	bool pressed = MoveUtil::isMoving();
	vec3_t pos = *player->getPos();

	if (boost) {
		if (speedDuration >= 0.158f) speedDuration *= duration;
		currSpeed = speedDuration;

		if (!viewBobbingEffective) {
			if (player->onGround && pressed) player->jumpFromGround();
			viewBobbingEffective = true;
		}
	}
	else { viewBobbingEffective = true; currSpeed = speed; }

	if (viewBobbing) {
		if (viewBobbingEffective) Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\xB8\x01\x00\x00\x00\x90\x90", 7);
		if (effectiveValue >= 0.00) effectiveValue = -0.0000000001;
	}
	else Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);

	// Vanilla, Jump
	if (mode.getSelectedValue() == 0 || mode.getSelectedValue() == 3)
		MoveUtil::setSpeed(currSpeed);

	float calcYaw = (player->yaw + 90) * (PI / 180);
	float c = cos(calcYaw);
	float s = sin(calcYaw);

	vec2_t moveVec2D = { input->forwardMovement, -input->sideMovement };
	moveVec2D = { moveVec2D.x * c - moveVec2D.y * s, moveVec2D.x * s + moveVec2D.y * c };
	vec3_t moveVec;

	// Hive
	if (mode.getSelectedValue() == 4) {
		hiveVelocity++;
		enabledTick++;

		float safeSpeedArray = hiveSpeedArray[hiveSpeedIndex++ % 15];

		if (pressed) {
			moveVec.x = moveVec2D.x * safeSpeedArray; moveVec.z = moveVec2D.y * safeSpeedArray;

			if (hiveVelocity >= 3) { hiveVelocity = 0; moveVec.y = -0.05f; }
			if (enabledTick >= 5 &&  pressed && !player->onGround) player->lerpMotion(moveVec);
		}
		else MoveUtil::stop(false);
	}

	// Cubecraft
	if (mode.getSelectedValue() == 5) {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
		player->velocity.y = 0;
		float ccspeed = 1.94f;

		if (!boost && player->onGround && pressed)
			player->jumpFromGround();

		if (input->isJumping) player->velocity.y = ccspeed / 6;
		if (input->isSneakDown) player->velocity.y = -ccspeed / 6;

		if (tick % 3 == 0) {
			moveVec.x = moveVec2D.x * ccspeed;
			moveVec.z = moveVec2D.y * ccspeed;
			moveVec.y = player->velocity.y;
		}
		else {
			g_Data.getClientInstance()->minecraft->setTimerSpeed(80.f);
			moveVec.x = moveVec2D.x * 0;
			moveVec.z = moveVec2D.y * 0;
			moveVec.y = player->velocity.y;
		}
		if (pressed) player->lerpMotion(moveVec);
		else {
			player->velocity.x = 0.f;
			player->velocity.z = 0.f;
		}
	}

	// Test
	if (mode.getSelectedValue() == 6) {
		MoveUtil::setSpeed(randomFloat(testfloat / 2, testfloat));
	}
}

void Flight::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	vec3_t pos;
	pos.x = player->getPos()->x;
	pos.y = player->getPos()->y;
	pos.z = player->getPos()->z;
	static int tick = 1; tick++;

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
	}

	if (packet->isInstanceOf<NetworkLatencyPacket>()) {
		auto* LatencyPacket = reinterpret_cast<NetworkLatencyPacket*>(packet);
	}
}

void Flight::onDisable() {
	Utils::patchBytes((unsigned char*)ViewBobbing, (unsigned char*)"\x0F\xB6\x80\xDB\x01\x00\x00", 7);
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto speedMod = moduleMgr->getModule<Speed>();
	auto blink = moduleMgr->getModule<Blink>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	MoveUtil::fullStop(false);

	if (speedWasEnabled) { speedMod->setEnabled(true); speedWasEnabled = false; }
	if (viewBobbing) player->onGround = false;
	velocityEffective = false;
	blink->setEnabled(false);

	hiveSpeedIndex = 0;
	hiveVelocity = 0;
	enabledTick = 0;
	hiveTick = 0;

	// Jump
	if (mode.getSelectedValue() == 3) hasJumped = false;
}