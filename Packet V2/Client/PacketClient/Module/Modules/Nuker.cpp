#include "Nuker.h"

Nuker::Nuker() : IModule(0, Category::MISC, "fucks earth") {
	registerBoolSetting("AutoDestroy", &autodestroy, autodestroy);
	registerBoolSetting("VeinMiner", &veinMiner, veinMiner);
	registerIntSetting("Up", &up, up, 0, 15);
	registerIntSetting("Down", &down, down, 1, 255);
	registerIntSetting("Radius", &nukerRadius, nukerRadius, 1, 15);
#ifdef _DEBUG
	registerBoolSetting("Treeos", &tree, tree);
#endif
}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	return ("Nuker");
}

void Nuker::onTick(C_GameMode* gm) {
	if (autodestroy) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - nukerRadius; x < pos->x + nukerRadius; x++) {
			for (int z = (int)pos->z - nukerRadius; z < pos->z + nukerRadius; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					gm->destroyBlock(&blockPos, 1);
				}
			}
		}
	} else if (tree && !autodestroy) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - nukerRadius; x < pos->x + nukerRadius; x++) {
			for (int z = (int)pos->z - nukerRadius; z < pos->z + nukerRadius; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					bool destroy = false;
					int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;

					if (id == 17 || id == 18 && tree) destroy = true;

					if (destroy) {
						gm->destroyBlock(&blockPos, 1);
					}
				}
			}
		}
	}
}