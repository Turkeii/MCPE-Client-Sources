#include "autoWalk.h"

autoWalk::autoWalk() : IModule(0x0, Category::MOVEMENT, "Auto work") {
}

autoWalk::~autoWalk() {
}

const char* autoWalk::getModuleName() {
	return ("AutoDash");
}

void autoWalk::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	g_Data.getClientInstance()->getMoveTurnInput()->forward = true;
	player->setSprinting(false);
}

void autoWalk::onDisable() {
	g_Data.getClientInstance()->getMoveTurnInput()->forward = false;
}
