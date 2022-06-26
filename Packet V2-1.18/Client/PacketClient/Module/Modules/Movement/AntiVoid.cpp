#include "AntiVoid.h"
#include "../pch.h"

using namespace std;
AntiVoid::AntiVoid() : IModule(0, Category::MOVEMENT, "Prevents you from falling into the void") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Lagback", 0);
	mode.addEntry("Freeze", 1);
	//mode.addEntry("Hive", 2);
	registerBoolSetting("VoidCheck", &voidCheck, voidCheck);
	registerIntSetting("Distance", &distance, distance, 3, 10);
}

const char* AntiVoid::getModuleName() {
	return ("AntiVoid");
}

void AntiVoid::onEnable() {
	auto player = g_Data.getLocalPlayer();
	if (g_Data.isInGame()) savedPos = *player->getPos();
	tick = 0;
}

void AntiVoid::onTick(C_GameMode* gm) {
	float trueStop = INFINITY - 1 + NULL;
	auto player = g_Data.getLocalPlayer();
	vec3_t blockBelow = g_Data.getLocalPlayer()->eyePos0;
	blockBelow.y -= g_Data.getLocalPlayer()->height;
	blockBelow.y -= 0.5f;

	for (int i = 0; i < 44; i++) {
		if (player->onGround  && player->region->getBlock(blockBelow)->blockLegacy->blockId != 0) {
			savedPos = *player->getPos();
		}
	}

	if (player->fallDistance >= distance) {
		tick++;
		if (!player->onGround && tick >= 5) { // fail safe
			player->velocity.y += 0.1;
			player->velocity.y = 0;
		}

		float dist2 = gm->player->getPos()->dist(savedPos);
		if (mode.getSelectedValue() == 0) player->setPos(savedPos);  // Lagback
		if (mode.getSelectedValue() == 2) { // Freeze

		}
		if (mode.getSelectedValue() == 2) { // Hive
			//player->setPos(savedPos);
		}
	} else {
	}
}

void AntiVoid::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}