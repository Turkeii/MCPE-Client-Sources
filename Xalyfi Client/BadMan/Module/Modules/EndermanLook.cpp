#include "EndermanLook.h"

EndermanLook::EndermanLook() : IModule(0x0, Category::PLAYER, "stops you from looking at enderman") {
}

EndermanLook::~EndermanLook() {
}

const char* EndermanLook::getModuleName() {
	return ("EndermanLook");
}

void EndermanLook::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	
	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		PlayerAuthInputPacket* AuthPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		AuthPacket->pitch = 90.f;
	}
	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		PlayerAuthInputPacket* MovePacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		MovePacket->pitch = 90.f;
	}
}