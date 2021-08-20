#include "autoWalk.h"

autoWalk::autoWalk() : IModule(0x0, Category::MOVEMENT, "Walks where you are looking") {
}

autoWalk::~autoWalk() {
}

const char* autoWalk::getModuleName() {
	return ("AutoWalk");
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
