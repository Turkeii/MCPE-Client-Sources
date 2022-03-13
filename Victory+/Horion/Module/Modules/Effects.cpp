#include "Effects.h"

teste::teste() : IModule(0, Category::VISUAL, "Visible Effects!") {
	this->registerBoolSetting("Invisible", &this->Invisible, this->Invisible);
	this->registerBoolSetting("Freeze", &this->Freeze, this->Freeze);
	this->registerBoolSetting("Fire", &this->Fire, this->Fire);
}

teste::~teste() {
}

const char* teste::getModuleName() {
	return ("Effect");
}

void teste::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (Invisible) {
		player->isInvisible();
	}
	if (Fire) {
		player->isOnFire();
	}
	if (Freeze) {
		player->thawFreezeEffect();
	}
}