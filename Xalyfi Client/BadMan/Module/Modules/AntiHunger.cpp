#include "AntiHunger.h"

AntiHunger::AntiHunger() : IModule(0x0, Category::PLAYER, "Slows down the rate in which you lose hunger") {
	registerBoolSetting("OnGround spoof", &this->ground, this->ground);
}

AntiHunger::~AntiHunger() {
}

const char* AntiHunger::getModuleName() {
	return ("AntiHunger");
}

void AntiHunger::onSendPacket(C_Packet* packet){
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}
}