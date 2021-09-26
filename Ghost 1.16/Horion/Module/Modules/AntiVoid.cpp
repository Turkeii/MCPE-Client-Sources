#include "AntiVoid.h"

AntiVoid::AntiVoid() : IModule(0, Category::MOVEMENT, "Automatically teleports you back up if you fall down more than X blocks. Buggy") {
	registerIntSetting("distance", &this->distance, this->distance, 1, 30);
}

AntiVoid::~AntiVoid() {
}

const char* AntiVoid::getModuleName() {
	return ("AntiVoid");
}

void AntiVoid::onTick(C_GameMode* gm) {
	C_LocalPlayer* player = g_Data.getLocalPlayer();
	vec3_t blockBelow = player->eyePos0;
	blockBelow.y -= player->height;
	blockBelow.y -= 2.f;

	if (((player->region->getBlock(blockBelow)->blockLegacy))->blockId != 0 && ((player->region->getBlock(blockBelow)->blockLegacy))->material->isSolid) {
		savepos = blockBelow;
		savepos.y += player->height;
		savepos.y += 2.f;
	}

	if (player->fallDistance >= distance) {
		player->setPos(savepos);
	}
}
