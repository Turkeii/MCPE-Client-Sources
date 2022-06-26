#include "Blink.h"
#include "../pch.h"

Blink::Blink() : IModule(0, Category::PLAYER, "Lags you server-sided") {
}

Blink::~Blink() {
	getMovePlayerPacketHolder()->clear();
	getPlayerAuthInputPacketHolder()->clear();
}

const char* Blink::getModuleName() {
	return ("Blink");
}

void Blink::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	player->fallDistance = 0.f;
}