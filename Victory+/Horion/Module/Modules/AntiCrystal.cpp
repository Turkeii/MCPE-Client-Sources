#include "AntiCrystal.h"
#include "../../../Utils/Logger.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

AntiCrystal::AntiCrystal() : IModule(0x0, Category::PLAYER, "Reduces damage from end crystals.") {
    //registerFloatSetting("AutoRange", &this->range, this->range, 1.f, 15.f);
	registerBoolSetting("2b2e", &this->Bypass, this->Bypass);
	registerIntSetting("Reduces", &this->distance, this->distance, 1, 3);
}

AntiCrystal::~AntiCrystal() {
}

const char* AntiCrystal::getModName() {
	if (Auto) {
		return "";
	}
	else {
		return "";
	}
}

const char* AntiCrystal::getModuleName() {
	return ("AntiCrystal");
}

const char* AntiCrystal::getRawModuleName() {
	return "AntiCrystal";
}

void AntiCrystal::onSendPacket(C_Packet* packet) {
	if (g_Data.isInGame()) {
		vec3_t* pos = g_Data.getLocalPlayer()->getPos();
		if (!Bypass) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
				PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				InputPacket->pos.y = static_cast<float>(pos->y - distance);
			}
		} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
			C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
			movePacket->Position.y = static_cast<float>(pos->y + distance);
		}
		if (Bypass) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
				PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				if (Auto && crystal) {
					InputPacket->pos.y = static_cast<float>(pos->y - 0.3);
				}
			} else if (packet->isInstanceOf<C_MovePlayerPacket>()) {
				C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				movePacket->Position.y = static_cast<float>(pos->y + 0.3);
			}
		}
	}
}