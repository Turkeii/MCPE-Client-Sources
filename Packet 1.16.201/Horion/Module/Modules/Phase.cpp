#include "../../Module/ModuleManager.h"
#include "Phase.h"

Phase::Phase() : IModule(0, Category::MOVEMENT, "Walk through walls") {
	this->registerBoolSetting("Vertical", &this->vertMode, this->vertMode);
}

Phase::~Phase() {
}

const char* Phase::getModuleName() {
	return ("NoClip");
}

void Phase::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;

	if (vertMode) {
		gm->player->aabb.upper.y = 0.f;
	}
}

void Phase::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->aabb.upper.y += 1.8f;
	if (vertMode) {
		auto phaseMod = moduleMgr->getModule<Phase>();
			if (phaseMod->vertMode == true);
			phaseMod->vertMode = false;
	}
}