#include "XP.h"

XP::XP() : IModule(0, Category::PLAYER, "Gives you experience levels") {
	this->registerBoolSetting("Levels", &this->levels, this->levels);
	this->registerIntSetting("Amount", &this->amount, this->amount, 1, 250);
}

const char* XP::getModuleName() {
	return "XP";
}

void XP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (levels) {
		player->addLevels(amount);
	} else {
		player->addExperience(amount);
	}
}