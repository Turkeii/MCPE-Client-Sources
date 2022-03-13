#include "AirWalk.h"

AirWalk::AirWalk() : IModule(0, Category::PLAYER, "Become stuck.") {
}

AirWalk::~AirWalk() {
}

const char* AirWalk::getModuleName() {
	return ("AirWalk");
}

void AirWalk::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	gm->player->velocity.y = 0;
}
