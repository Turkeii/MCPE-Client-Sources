#include "Derp.h"

Derp::Derp() : IModule(0, Category::MISC, "lol you stupid") {
	registerBoolSetting("Headless", &headless, headless);
	registerBoolSetting("Twerk", &twerk, twerk);
	registerBoolSetting("Spin", &spin, spin);
	registerBoolSetting("Silent", &silent, silent);
	registerIntSetting("Delay", &delay, delay, 0, 10);
}

Derp::~Derp() {
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
	if (headless && !silent) {
		gm->player->pitch = -180;
	}
	if (twerk) {
		tick++;
		if (tick >= delay) {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
			tick = -2;
		} else {
			g_Data.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		}
	}
}

void Derp::onPostRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	float prevyaw = player->yawUnused1;
	float prevyaw2 = player->yaw;
	float prevyaw3 = player->yaw2;
	if (spin && !silent) {
		player->bodyYaw = (float)(rand() % 360);
		player->yawUnused2 = (float)(rand() % 360);
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
