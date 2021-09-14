#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Each hit is a critical hit") {
	registerBoolSetting("Test", &tester, tester);
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
	return ("X Criticals");
}

void Criticals::onTick(C_GameMode* gm) {
	if (tester) {
		gm->player->onGround = false;
		return;
	}
}

void Criticals::onSendPacket(C_Packet* packet) {
	if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		movePacket->onGround = false;
	}
}
