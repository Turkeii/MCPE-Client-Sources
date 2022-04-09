#include "Nuker.h"

#include "../ModuleManager.h"

Nuker::Nuker() : IModule(0x0, Category::WORLD, "Break multiple blocks at once") {
	registerIntSetting("radius", &nukerRadius, nukerRadius, 1, 15);
	registerBoolSetting("veinminer", &veinMiner, veinMiner);
	registerIntSetting("Height +", &up, up, 1, 10);
	registerIntSetting("Height -", &down, down, 1, 10);
}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	return "Nuker";
}

void Nuker::onTick(C_GameMode* gm) {
	vec3* pos = gm->player->getPos();
	for (int x = (int)pos->x - nukerRadius; x < pos->x + nukerRadius; x++) {
		for (int z = (int)pos->z - nukerRadius; z < pos->z + nukerRadius; z++) {
			for (int y = (int)pos->y - down; y < pos->y + up; y++) {
				vec3i blockPos = vec3i(x, y, z);
				bool destroy = true;
				int id = gm->player->region->getBlock(blockPos)->toLegacy()->blockId;
				if (destroy) {
					gm->destroyBlock(&blockPos, 1);
				}
			}
		}
	}
}