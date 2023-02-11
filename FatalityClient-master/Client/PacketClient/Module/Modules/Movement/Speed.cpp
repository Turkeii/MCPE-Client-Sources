#include "Speed.h"
#include "../pch.h"

bool testOnGround = false;
float speedMax = 0.69f; // inf value
float speedMin = 0.59f; // inf value
int packetsSent = 0;
int enabledTicks = 0;

using namespace std;
Speed::Speed() : IModule(0, Category::MOVEMENT, "Increases your speed") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("(Vanilla)", 0);
	mode.addEntry("(HiveHop)", 1);
	mode.addEntry("(HiveLow)", 2);
	mode.addEntry("(OldHop)", 3);
	mode.addEntry("(Cubecraft)", 4);
	mode.addEntry("(Friction)", 5);
	mode.addEntry("(Boost)", 6);
	mode.addEntry("(Test)", 7);
	// Vanilla
	registerFloatSetting("Height", &height, height, 0.000001f, 0.40f);
	// All Settings
	registerBoolSetting("Bypass", &autoJump, autoJump);
	registerFloatSetting("Speed", &speed, speed, 0.2f, 2.f);
	registerIntSetting("Timer", &timer, timer, 20, 35);

	// Friction
	registerFloatSetting("SpeedMax", &speedMax, speedMax, 0.f, 2.f);
	registerFloatSetting("SpeedMin", &speedMin, speedMin, 0.f, 2.f);
	registerFloatSetting("Duration", &duration, duration, 0.5f, 1.05f);
}

const char* Speed::getRawModuleName() {
	return "Speed";
}

const char* Speed::getModuleName() {
	name = string("Speed ") + string(GRAY) + mode.GetEntry(mode.getSelectedValue()).GetName();
	return name.c_str();
}

void Speed::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	enabledTicks = 0;
}

void Speed::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (enabledTicks > 10) enabledTicks++;
	else enabledTicks = 0;

	if (player->onGround) { groundTicks++; offGroundTicks = 0; }
	else { offGroundTicks++; groundTicks = 0; }

	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	g_Data.getClientInstance()->minecraft->setTimerSpeed(timer);

	// HiveLow
	switch (mode.getSelectedValue()) {
	case 3: // Cubecraft
		ticks++;
		break;
	}
}

void Speed::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	bool pressed = MoveUtil::keyPressed();
	if (!pressed) MoveUtil::stop(false);
	player->setSprinting(true);

	// Vanilla
	if (mode.getSelectedValue() == 0) {
		static bool useVelocity = false;
		// eat my absctrionalie
		if (height >= 0.385) { if (player->onGround && pressed) player->jumpFromGround(); useVelocity = false; }
		else useVelocity = true;
		if (height <= 0.04 && !input->isJumping) { player->velocity.y += height; useVelocity = false; }

		if (player->onGround && useVelocity && pressed && !input->isJumping) player->velocity.y = height;
		MoveUtil::setSpeed(speed);
	}

	// Hive Old (OldHop)
	if (mode.getSelectedValue() == 3) {
		speedFriction *= 0.9400610828399658f;
		if (pressed) {
			if (player->onGround) {
				player->jumpFromGround();
				speedFriction = randomFloat(0.5285087823867798f, 0.49729517102241516f);
			}
			else MoveUtil::setSpeed(speedFriction);
		}
	}

	// HiveSafe
	if (mode.getSelectedValue() == 1) {
		speedFriction *= 0.9300610828399658f;
		if (pressed) {
			if (player->onGround) {
				player->jumpFromGround();
				speedFriction = randomFloat(0.5085087823867798f, 0.47729517102241516f);
			}
			else MoveUtil::setSpeed(speedFriction);
		}
	}

	// HiveLow
	if (mode.getSelectedValue() == 2) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		float c = cos(calcYaw);
		float s = sin(calcYaw);

		vec2_t moveVec2D = { input->forwardMovement, -input->sideMovement };
		moveVec2D = { moveVec2D.x * c - moveVec2D.y * s, moveVec2D.x * s + moveVec2D.y * c };
		vec3_t moveVec;

		if (!pressed)
			MoveUtil::stop(false);

		static bool useVelocity = false;
		if (0.5000000059604645 >= 0.285) {
			if (player->onGround && pressed) player->jumpFromGround();
			useVelocity = false;
		}
		else
			useVelocity = true;

		if (0.5000000059604645 <= 0.03 && !input->isJumping) {
			player->velocity.y += 0.5000000059604645;
			useVelocity = false;
		}

		speedFriction *= 0.8046240322113025;
		if (pressed) {
			player->setSprinting(true);
			if (player->onGround) {
				if (useVelocity && !input->isJumping) player->velocity.y = 0.5000000059604645;
				speedFriction = randomFloat(0.799079251289367, 0.84846795992851257);
			}
			else
				MoveUtil::setSpeed(speedFriction);
			if (player->onGround) {
				moveVec.y = player->velocity.y = 0.35f;
			}
		}

		// Cubecraft
		if (mode.getSelectedValue() == 4) {
			float calcYaw = (player->yaw + 90) * (PI / 180);
			float c = cos(calcYaw);
			float s = sin(calcYaw);

			vec2_t moveVec2D = { input->forwardMovement, -input->sideMovement };
			moveVec2D = { moveVec2D.x * c - moveVec2D.y * s, moveVec2D.x * s + moveVec2D.y * c };
			vec3_t moveVec;

			speedFriction *= 0.97;
			if (ticks % 3 == 0) {
				moveVec.x = moveVec2D.x * speedFriction;
				moveVec.z = moveVec2D.y * speedFriction;
				moveVec.y = player->velocity.y;
			}
			else {
				g_Data.getClientInstance()->minecraft->setTimerSpeed(17.f);
				moveVec.x = moveVec2D.x * speedFriction / 3;
				moveVec.z = moveVec2D.y * speedFriction / 3;
				moveVec.y = player->velocity.y;
			}

			if (pressed) {
				player->lerpMotion(moveVec);
				if (player->onGround) {
					speedFriction = randomFloat(speedMin, speedMax);
					player->jumpFromGround();
				}
			}
		}

		// Friction
		if (mode.getSelectedValue() == 5) {
			static bool useVelocity = false;
			// eat my absctrionalie
			if (height >= 0.385) { if (player->onGround && pressed) player->jumpFromGround(); useVelocity = false; }
			else useVelocity = true;
			if (height <= 0.03 && !input->isJumping) { player->velocity.y += height; useVelocity = false; }

			speedFriction *= duration;
			if (pressed) {
				if (player->onGround) {
					if (useVelocity && !input->isJumping) player->velocity.y = height;
					speedFriction = randomFloat(speedMin, speedMax);
				}
				else MoveUtil::setSpeed(speedFriction);
			}
		}
		if (autoJump) {
			C_LocalPlayer* player = g_Data.getLocalPlayer();

			if (player->onGround) player->jumpFromGround();
		}

		// Boost
		if (mode.getSelectedValue() == 6) {
			static bool useVelocity = false;
			// eat my absctrionalie
			if (height >= 0.385) { if (player->onGround && pressed) player->jumpFromGround(); useVelocity = false; }
			else useVelocity = true;
			if (height <= 0.04 && !input->isJumping) { player->velocity.y += height; useVelocity = false; }

			if (pressed && player->onGround) {
				if (useVelocity && !input->isJumping) player->velocity.y = height;
				MoveUtil::setSpeed(speed);
			}
		}

		// Test
		if (mode.getSelectedValue() == 6) {
			float calcYaw = (player->yaw - 90) * (PI / 180);
			float calcPitch = (player->pitch) * (PI / 180);
			vec3_t rotVec;
			rotVec.x = cos(calcYaw) * randomFloat(.5f, 1.f);
			rotVec.y = sin(calcPitch) * randomFloat(.5f, 1.f);
			rotVec.z = sin(calcYaw) * randomFloat(.5f, 1.f);

			if (pressed) {
				if (MoveUtil::isMoving()) {
					C_MovePlayerPacket p2 = C_MovePlayerPacket(g_Data.getLocalPlayer(), player->getPos()->add(vec3_t(rotVec.x / randomFloat(1.1f, 2.2f), 0.f, rotVec.z / randomFloat(1.1f, 2.2f))));
					g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&p2);
					packetsSent++;
				}
				if (player->onGround) {
					speedFriction = randomFloat(speedMin, speedMax);
				}
				else {
					speedFriction = randomFloat(.33f, .45f);
				}
				MoveUtil::setSpeed(speedFriction);
			}
		}
	}
}

void Speed::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto scaffold = moduleMgr->getModule<Scaffold>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr || input == nullptr) return;
}

void Speed::onDisable() {
	g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	MoveUtil::stop(false);

	preventKick = false;
	packetsSent = 0;
}