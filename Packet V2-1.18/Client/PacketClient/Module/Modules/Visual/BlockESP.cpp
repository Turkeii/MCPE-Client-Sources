#include "BlockESP.h"
#include "../pch.h"

BlockESP::BlockESP() : IModule(0, Category::VISUAL, "Outlines Blocks") {
	registerBoolSetting("Spawners", &spawner, spawner);
	registerBoolSetting("Redstone", &rOre, rOre);
	registerBoolSetting("Emeralds", &eOre, eOre);
	registerBoolSetting("Diamonds", &dOre, dOre);
	registerBoolSetting("Iron", &iOre, iOre);
	registerBoolSetting("Gold", &gOre, gOre);
	registerBoolSetting("Coal", &cOre, cOre);
	registerIntSetting("Range", &range, range, 1, 15);
	registerFloatSetting("Width", &width, width, 0.3, 1);
}

const char* BlockESP::getModuleName() {
	return ("BlockESP");
}

void BlockESP::onPreRender(C_MinecraftUIRenderContext* renderCtx) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (g_Data.canUseMoveKeys()) {
		vec3_t* pos = player->getPos();
		for (int x = (int)pos->x - range; x < pos->x + range; x++) {
			for (int z = (int)pos->z - range; z < pos->z + range; z++) {
				for (int y = (int)pos->y - range; y < pos->y + range; y++) {
					vec3_t blockPos = vec3_t(x, y, z);
					vec3_t angle = blockPos;
					angle = angle.floor();
					angle.x += 1.f;
					angle.y += 1.f;
					angle.z += 1.f;

					int id = (int)player->region->getBlock(blockPos)->toLegacy()->blockId;
					bool dRender = false;
					bool eRender = false;
					bool rRender = false;
					bool gRender = false;
					bool iRender = false;

					if (id == 56 && dOre) dRender = true;   // Diamond
					if (id == 129 && eOre) eRender = true;  // Emerald
					if (id == 73 && rOre) rRender = true;   // Redstone
					if (id == 74 && rOre) rRender = true;   // Redstone
					if (id == 14 && gOre) gRender = true;   // Gold
					if (id == 15 && iOre) iRender = true;   // Iron

					if (dRender) {
						DrawUtils::setColor(0.2, 0.9, 1, 1);
						DrawUtils::drawBox(blockPos, angle, width, 1);
					} else if (eRender) {
						DrawUtils::setColor(0, 0.7, 0, 1);
						DrawUtils::drawBox(blockPos, angle, width, 1);
					} else if (rRender) {
						DrawUtils::setColor(0.8, 0, 0, 1);
						DrawUtils::drawBox(blockPos, angle, width, 1);
					} else if (gRender) {
						DrawUtils::setColor(1, 0.7, 0, 1);
						DrawUtils::drawBox(blockPos, angle, width, 1);
					} else if (iRender) {
						DrawUtils::setColor(1, 0.9, 0.8, 1);
						DrawUtils::drawBox(blockPos, angle, width, 1);
					}
				}
			}
		}
	}
}