#include "AntiBlock.h"

AntiBlock::AntiBlock() : IModule(VK_NUMPAD9, Category::MISC, "Destroys blocks around you") {
	registerIntSetting("Range", &this->range, this->range, 1, 5);
	registerBoolSetting("Beds", &this->beds, this->beds);
	registerBoolSetting("Anvil", &this->anvil, this->anvil);
	registerBoolSetting("Anchor", &this->anchor, this->anchor);
	registerBoolSetting("Cactus", &this->cactus, this->cactus);
	registerBoolSetting("TNT", &this->tnt, this->tnt);
}

AntiBlock::~AntiBlock() {
}

const char* AntiBlock::getModuleName() {
	return ("AntiBlock");
}

void AntiBlock::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 26 && this->beds) destroy = true;     // Beds
				if (id == 145 && this->anvil) destroy = true;    // Cakes
				if (id == 527 && this->anchor) destroy = true;  // Chests
				if (id == 81 && this->cactus) destroy = true;    // Barrels
				if (id == 46 && this->tnt) destroy = true;      // Redstone

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