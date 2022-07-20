#include "SignFucker.h"

SignFucker::SignFucker() : IModule(0x0, Category::WORLD, "Destroys signs") {
	registerIntSetting("Range", &this->range, this->range, 1, 10);
}

SignFucker::~SignFucker() {
}

const char* SignFucker::getModuleName() {
	return ("Sign Fucker");
}

void SignFucker::onTick(C_GameMode* gm) {
	vec3_t* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				vec3_ti blockPos = vec3_ti(x, y, z);
				bool destroy = false;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 68 || 
					id == 63 || 
					id == 436 ||
					id == 437 || 
					id == 441 || 
					id == 442 || 
					id == 443 || 
					id == 444 || 
					id == 445 || 
					id == 446 || 
					id == 447 || 
					id == 448 ||
					id == 505 ||
					id == 506 ||
					id == 507 ||
					id == 508) destroy = true;  // all the sign id's

				if (destroy) {
					gm->destroyBlock(&blockPos, 0);
					if (!moduleMgr->getModule<NoSwing>()->isEnabled())
						g_Data.getLocalPlayer()->swingArm();
					return;
				}
			}
		}
	}
}
