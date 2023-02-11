#include "Nuker.h"
#include "../pch.h"

Nuker::Nuker() : IModule(0, Category::OTHER, "Destroys all blocks around you") {
	registerBoolSetting("VeinMiner", &veinMiner, veinMiner);
	registerIntSetting("Radius", &radius, radius, 1, 15);
	registerIntSetting("Down", &down, down, 1, 15);
	registerIntSetting("Up", &up, up, 0, 15);
}

const char* Nuker::getModuleName() {
	return ("Nuker");
}

void Nuker::onTick(C_GameMode* gm) {
	if (!veinMiner) {
		vec3_t* pos = gm->player->getPos();
		for (int x = (int)pos->x - radius; x < pos->x + radius; x++) {
			for (int z = (int)pos->z - radius; z < pos->z + radius; z++) {
				for (int y = (int)pos->y - down; y < pos->y + up; y++) {
					vec3_ti blockPos = vec3_ti(x, y, z);
					gm->destroyBlock(&blockPos, 1);
				}
			}
		}
	}
}