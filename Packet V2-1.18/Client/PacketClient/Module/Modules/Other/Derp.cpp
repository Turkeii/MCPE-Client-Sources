#include "Derp.h"
#include "../pch.h"

Derp::Derp() : IModule(0, Category::OTHER, "Makes you look retarded") {
	registerBoolSetting("Headless", &headless, headless);
	registerBoolSetting("Twerk", &twerk, twerk);
	registerBoolSetting("Spin", &spin, spin);
	registerBoolSetting("Silent", &silent, silent);
	registerFloatSetting("Speed", &speed, speed, 1, 50);
	registerIntSetting("Delay", &delay, delay, 0, 10);
}

const char* Derp::getModuleName() {
	return "Derp";
}

void Derp::onEnable() {
	tick = -2;
}

void Derp::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (twerk) {
		tick++;
		if (tick >= delay) { g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true; tick = -2; }
		else g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
	}
}

void Derp::onPlayerTick(C_Player* plr) {
	if (plr == nullptr || silent) return;

	if (headless) plr->pitch = -180;
	if (spin) {
		// i will figure this out later
	}
}

void Derp::onSendPacket(C_Packet* packet) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	auto player = g_Data.getLocalPlayer();
	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
	auto* authPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
	if (packet->isInstanceOf<C_MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
		if (g_Data.isInGame() && g_Data.canUseMoveKeys()) {
			if (silent) {
				if (headless) {
					movePacket->pitch = -180;
					authPacket->pitch = -180;
				}
				if (spin) {
					movePacket->headYaw = (float)(rand() % 360);
					movePacket->yaw = (float)(rand() % 360);
					movePacket->headYaw = movePacket->yaw;
					movePacket->yaw = movePacket->headYaw;
				}
			} else if (spin) {
				movePacket->headYaw = (float)(rand() % 360);
				movePacket->yaw = (float)(rand() % 360);
				movePacket->headYaw = movePacket->yaw;
				movePacket->yaw = movePacket->headYaw;
			}
		}
	}
}

void Derp::onDisable() {
	if (twerk) g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
}
