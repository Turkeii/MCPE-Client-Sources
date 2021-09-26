#include "Insane.h"

Insane::Insane() : IModule(0, Category::WORLD, "Insane") {
	registerBoolSetting("Insane", &this->insane, this->insane);
	registerBoolSetting("Emo (Die)", &this->die, this->die);
	registerBoolSetting("Dissapear", &this->dimension, this->dimension);
	registerBoolSetting("Eat Totem", &this->totem, this->totem);
}

Insane::~Insane() {
}

const char* Insane::getModuleName() {
	return ("Insane");
}

void Insane::onEnable() {
}

void Insane::onTick(C_GameMode* gm) {
	if (this->insane) {
		auto player = g_Data.getLocalPlayer();
		player->animateHurt();
		player->setGameModeType(1);
		player->fallDistance = 100;
		gm->player->damageTime = 100.f;
		auto movePacket = g_Data.getLocalPlayer();
		movePacket->setOnFire(true);
		movePacket->doWaterSplashEffect();
	}
	if (this->die) {
		auto player = g_Data.getLocalPlayer();
		player->kill();
	}
	if (this->dimension) {
		auto player = g_Data.getLocalPlayer();
		player->canChangeDimensions();
		player->changeDimension(3);
	}
	if (this->totem) {
		auto movePacket = g_Data.getLocalPlayer();
		movePacket->consumeTotem();
	}
}

void Insane::onDisable() {
}
