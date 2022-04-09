#include "AutoClicker.h"

AutoClicker::AutoClicker() : IModule(0, Category::COMBAT, "Automatically clicks for you") {
	registerIntSetting("delay", &delay, delay, 0, 10);
}

AutoClicker::~AutoClicker() {
}

const char* AutoClicker::getModuleName() {
	return ("AutoClicker");
}

void AutoClicker::onTick(C_GameMode* gm) {
	if ((GameData::isLeftClickDown() || !hold) && GameData::canUseMoveKeys()) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
		Odelay++;

		if (Odelay >= delay) {
			auto selectedItem = localPlayer->getSelectedItem();
			if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
				return;

			g_Data.leftclickCount++;

			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				localPlayer->swingArm();

			if (pointing->hasEntity())
				gm->attack(pointing->getEntity());
			else if (breakBlocks) {
				bool isDestroyed = false;
				gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
				gm->stopDestroyBlock(pointing->block);
				if (isDestroyed && localPlayer->region->getBlock(pointing->block)->blockLegacy->blockId != 0)
					gm->destroyBlock(&pointing->block, 0);
			}
			Odelay = 0;
		}
	}
}