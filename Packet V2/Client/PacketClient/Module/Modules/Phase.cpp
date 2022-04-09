#include "../../Module/ModuleManager.h"
#include "Phase.h"

Phase::Phase() : IModule(0, Category::EXPLOIT, "Walk through blocks") {
	registerBoolSetting("Vertical", &vertMode, vertMode);
}

Phase::~Phase() {
}

const char* Phase::getRawModuleName() {
	return "Phase";
}

const char* Phase::getModuleName() {
	if (vertMode) {
		name = std::string("Phase ") + std::string(GRAY) + std::string("Vertical");
		return name.c_str();
	} else if (!vertMode) {
		return "Phase";
	}
}

void Phase::onTick(C_GameMode* gm) {
	gm->player->aabb.upper.y = gm->player->aabb.lower.y;

	if (vertMode)
		gm->player->aabb.upper.y = 0.f;
}

void Phase::onDisable() {
	if (g_Data.getLocalPlayer() != nullptr)
		g_Data.getLocalPlayer()->aabb.upper.y += 1.8f;
	if (vertMode) {
		vec3_t pPos = g_Data.getLocalPlayer()->eyePos0;
		vec3_t pos;
		pos.x = 0.f + pPos.x;
		pos.y = 0.000001f + pPos.y;
		pos.z = 0.f + pPos.z;
		g_Data.getLocalPlayer()->setPos(pos);
	}
}