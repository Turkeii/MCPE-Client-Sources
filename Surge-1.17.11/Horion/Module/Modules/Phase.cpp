#include "Phase.h"

Phase::Phase() : IModule('I', Category::MOVEMENT, "Walk through walls") {
	this->registerBoolSetting("Vertical", &this->vertical, this->vertical);
}

Phase::~Phase() {
}

const char* Phase::getModuleName() {
	return ("Phase");
}

void Phase::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;
	if (vertical) {
		gm->player->aabb.upper.y = 0.f;
	}
}

void Phase::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->aabb.upper.y += 1.8f;
}
