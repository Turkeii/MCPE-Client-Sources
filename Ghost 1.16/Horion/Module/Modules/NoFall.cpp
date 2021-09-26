#include "NoFall.h"

NoFall::NoFall() : IModule(0x0, Category::MOVEMENT, "It does nothing XD") {
}

NoFall::~NoFall() {
}

const char* NoFall::getModuleName() {
	return ("NoFall");
}

void NoFall::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->fallDistance = 0;
	gm->player->damageTime = 0.f;
}