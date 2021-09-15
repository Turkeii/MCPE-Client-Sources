#include "XP.h"

XP::XP() : IModule(0x0, Category::PLAYER, "Gives You Shit Loads Of XP!") {
	this->registerIntSetting("amount", &this->amount, this->amount, 1, 5000);
}

XP::~XP() {
}

const char* XP::getModuleName() {
	return ("XP");
}

void XP::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->addExperience(amount);
}