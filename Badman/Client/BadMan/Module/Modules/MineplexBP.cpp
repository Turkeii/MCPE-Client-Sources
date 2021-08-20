#include "MineplexBP.h"

MineplexBP::MineplexBP() : IModule(0x0, Category::SERVER, "Allows you to fly longer on mineplez") {
}

MineplexBP::~MineplexBP() {
}

const char* MineplexBP::getModuleName() {
	return ("MineplexBP");
}

void MineplexBP::onSendPacket(C_Packet* packet) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (packet->isInstanceOf<C_MovePlayerPacket>()) {
		C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
		if (counter == 5) {
			counter = 0;
		} else {
			movePacket->Position.y -= counter / 100;
			counter++;
		}
	}
}
