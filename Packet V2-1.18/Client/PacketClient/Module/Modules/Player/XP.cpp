#include "XP.h"
#include "../pch.h"

XP::XP() : IModule(0, Category::PLAYER, "Gives you experience levels") {
	registerIntSetting("Amount", &amount, amount, 1, 250);
	registerBoolSetting("Levels", &levels, levels);
}

const char* XP::getModuleName() {
	return "XP";
}

void XP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (levels) player->addLevels(amount);
	else player->addExperience(amount);
}