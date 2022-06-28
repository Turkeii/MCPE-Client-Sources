#include "AntiCrystal.h"

AntiCrystal::AntiCrystal() : IModule(0x0, Category::PLAYER, "Hacker shit") {
	registerBoolSetting("2b2e", &Bypass, Bypass);
	registerBoolSetting("Endzone", &endzone, endzone);
	registerBoolSetting("Sink", &sink, sink);
	registerFloatSetting("Height", &Height, Height, 0.f, 1.f);
}

AntiCrystal::~AntiCrystal() {
}
const char* AntiCrystal::getModName() {
	if (Bypass) {
		return " [2b2e]";
	} else {
		return " ";
	}
}
const char* AntiCrystal::getModuleName() {
	return ("AntiCrystal");
}

void AntiCrystal::onSendPacket(C_Packet* packet) {
	if (g_Data.getLocalPlayer() == nullptr) return;
	vec3_t* pos = g_Data.getLocalPlayer()->getPos();
	if (!Bypass && !endzone) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			InputPacket->pos.y = static_cast<float>(pos->y - 1);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y - 1);
		}
	}
	if (Bypass) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			InputPacket->pos.y = static_cast<float>(pos->y - Height);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y - Height);
		}
	}
	if (endzone) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			if (timer = 1) {
				InputPacket->pos.y = static_cast<float>(pos->y - 0.1);
			}
			if (timer = 2) {
				InputPacket->pos.y = static_cast<float>(pos->y - 0.3);
			}
			if (timer = 3) {
				InputPacket->pos.y = static_cast<float>(pos->y - 0.1);
			}
			if (timer = 4) {
				InputPacket->pos.y = static_cast<float>(pos->y - 0.6);
			}
			if (timer = 5) {
				timer = 0.f;
			}
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y - Height);
		}
	}
}