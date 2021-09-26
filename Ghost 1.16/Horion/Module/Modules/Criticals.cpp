#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Each hit is a critical hit") {
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
	return ("Criticals");
}

void Criticals::onSendPacket(C_Packet* packet) {
	auto movePacket = g_Data.getLocalPlayer();
	movePacket->onGround = false;
}