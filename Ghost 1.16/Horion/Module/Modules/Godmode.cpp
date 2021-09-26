#include "Godmode.h"

Godmode::Godmode() : IModule(0, Category::BLATANT, "Client sided Godmode") {
}

Godmode::~Godmode() {
}

const char* Godmode::getModuleName() {
	return "Godmode";
}

void Godmode::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	player->heal(1);
}