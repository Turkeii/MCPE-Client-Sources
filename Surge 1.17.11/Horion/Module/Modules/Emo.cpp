#include "Emo.h"

Emo::Emo() : IModule(0x0, Category::PLAYER, "Kill your self and no respawn.") {
}

Emo::~Emo() {
}

const char* Emo::getModuleName() {
	return ("Emo");
}

void Emo::onEnable() {
	auto player = g_Data.getLocalPlayer();
	player->kill();
}

//void Emo::onTick(C_GameMode* gm) {
//auto player = g_Data.getLocalPlayer();
//player->kill();
//}