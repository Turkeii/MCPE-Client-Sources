#include "SpinAtack.h"

SpinAtack::SpinAtack() : IModule(0x0, Category::MISC, "Spin") {
}

SpinAtack::~SpinAtack() {
}

const char* SpinAtack::getModuleName() {
	return ("Spin");
}

void SpinAtack::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->startSpinAttack();
}

//void SpinAtack::onTick(C_GameMode* gm) {
//auto player = g_Data.getLocalPlayer();
//player->kill();
//}