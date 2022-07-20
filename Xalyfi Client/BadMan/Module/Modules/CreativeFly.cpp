#include "CreativeFly.h"

CreativeFly::CreativeFly() : IModule(0, Category::MOVEMENT, "Sets the mayFly value to true") {
}

CreativeFly::~CreativeFly() {
}

const char* CreativeFly::getModuleName() {
	return ("Creative Fly");
}

void CreativeFly::onTick(C_GameMode* gm) {
	gm->player->canFly = true;

}

void CreativeFly::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		if (g_Data.getLocalPlayer()->gamemode != 1)
			g_Data.getLocalPlayer()->canFly = false;
}
