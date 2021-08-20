#include "NoClip.h"

NoClip::NoClip() : IModule(0x0, Category::MOVEMENT, "Phase through walls on all axis") {
}

NoClip::~NoClip() {
}

const char* NoClip::getModuleName() {
	return ("NoClip");
}

void NoClip::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y - (float)1.8f;
}

void NoClip::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->aabb.upper.y = g_Data.getLocalPlayer()->aabb.lower.y + (float)1.8f;
}
