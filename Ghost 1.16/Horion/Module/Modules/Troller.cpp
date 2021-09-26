
#include "Troller.h"

Troller::Troller() : IModule('V', Category::MISC, "Fly around, break stuff and place stuff then tp right back") {
}

Troller::~Troller() {
}

const char* Troller::getModuleName() {
	return ("Troller");
}

void Troller::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	gm->player->canFly = true;
	gm->player->fallDistance = 0.f;
}

void Troller::onEnable() {
	if (g_Data.getLocalPlayer() != nullptr) {
		oldPos = *g_Data.getLocalPlayer()->getPos();
	}
}

void Troller::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr) {
		g_Data.getLocalPlayer()->setPos(oldPos);
		if (g_Data.getLocalPlayer()->gamemode != 1)
			g_Data.getLocalPlayer()->canFly = false;
	}
}