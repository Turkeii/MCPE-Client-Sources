#include "HiveNuker.h"

HiveNuker::HiveNuker() : IModule(VK_NUMPAD9, Category::WORLD, "Destroys blocks around you") {
	registerIntSetting("Range", &this->range, this->range, 1, 8);
}

HiveNuker::~HiveNuker() {
}

const char* HiveNuker::getModuleName() {
	return ("HiveNuker");
}

void HiveNuker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (gm->player->region->getBlock(blockPos)->toLegacy()->blockId) destroy = true;

				if (destroy) {
					gm->destroyBlock(&blockPos, 0);
					//if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}
}
