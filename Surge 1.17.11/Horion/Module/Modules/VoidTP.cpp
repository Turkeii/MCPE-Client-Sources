#include "VoidTP.h"

Twerk::Twerk() : IModule(0x0, Category::MOVEMENT, "For testing") {
this->registerIntSetting("amount", &this->amount, this->amount, 0, 2);
}

Twerk::~Twerk() {
}

const char* Twerk::getModuleName() {
	return ("TestMod");
}

void Twerk::onEnable() {
	auto player = g_Data.getLocalPlayer();
	player->openInventory();
}

//void Twerk::onTick(C_GameMode* gm) {
	//auto player = g_Data.getLocalPlayer();
	//player->kill();
//}