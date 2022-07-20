#include "XalyfiNinja.h"

AntiCrystal::AntiCrystal() : IModule(0x0, Category::COMBAT, "Work...?") {
	registerBoolSetting("Bypass", &this->Bypass, this->Bypass);
}

AntiCrystal::~AntiCrystal() {
}

const char* AntiCrystal::getModuleName() {
	return ("AntiCrystal");
}

void AntiCrystal::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void AntiCrystal::onTick(C_GameMode* gm) {
	if (g_Data.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}

void AntiCrystal::onSendPacket(C_Packet* packet) {
	if (!Bypass) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			InputPacket->pos.y = static_cast<float>(pos->y - 2);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y - 2);
		}
	}
	if (Bypass) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
			PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			InputPacket->pos.y = static_cast<float>(pos->y - 0.25f);
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y - 0.25f);
		}
	}
}