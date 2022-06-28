#include "Blink.h"

Blink::Blink() : IModule(0, Category::MISC, "allows u to move without being seen") {
}

Blink::~Blink() {
	getMovePlayerPacketHolder()->clear();
	getPlayerAuthInputPacketHolder()->clear();
}

const char* Blink::getModuleName() {
	return ("Blink");
}

void Blink::onTick(C_GameMode* gm) {
	gm->player->fallDistance = 0.f;
}
