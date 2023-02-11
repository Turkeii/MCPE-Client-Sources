#include "FastPlace.h"
#include "../pch.h"

FastPlace::FastPlace() : IModule(0, Category::PLAYER, "Changes the block placing delay") {
	registerIntSetting("Delay", &delay, delay, 0, 10);
}

const char* FastPlace::getModuleName() {
	return ("FastPlace");
}

void FastPlace::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
	C_Block* block = g_Data.getLocalPlayer()->region->getBlock(pointing->block);
	int blockID = (int)block->toLegacy()->blockId;

	if (g_Data.isRightClickDown() && g_Data.canUseMoveKeys()) {
		Odelay++;
		if (Odelay >= delay) {
			g_Data.rightclickCount++;
			if (blockID != 0) gm->buildBlock(new vec3_ti(pointing->block), pointing->blockSide);
		}
		Odelay = 0;
	}
}