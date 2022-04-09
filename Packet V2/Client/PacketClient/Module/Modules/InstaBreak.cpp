#include "InstaBreak.h"

InstaBreak::InstaBreak() : IModule(0, Category::EXPLOIT, "Break any block instantly") {
	registerBoolSetting("Hold", &breakBlocks, breakBlocks); 
	//registerBoolSetting("Hive", &hive, hive); 
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}

void InstaBreak::onEnable() {
	i = 0;
}

void InstaBreak::onTick(C_GameMode* gm) {
	if (i == 5) {
		i = 0;
	} else {
		i++;
	}
	if (g_Data.canUseMoveKeys()) {
		if (hive) {
			gm->player->canFly = false;
			if (breakBlocks) {
				if (g_Data.isLeftClickDown()) {
					PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
					gm->destroyBlock(&pointing->block, pointing->blockSide);
					g_Data.getLocalPlayer()->setGameModeType(1);
					i = 0;
				}
			} else {
				if (g_Data.isLeftClickDown()) {
					g_Data.getLocalPlayer()->setGameModeType(1);
					i = 0;
				}
			}
			if (g_Data.isLeftClickDown() || g_Data.isLeftClickDown() && i >= 5) {
				g_Data.getLocalPlayer()->setGameModeType(0);
			}
		} else if (breakBlocks && !hive) {
			if (!g_Data.isLeftClickDown())
				return;
			PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
			gm->destroyBlock(&pointing->block, pointing->blockSide);
		}
	}
}