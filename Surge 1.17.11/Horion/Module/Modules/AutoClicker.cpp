#include "AutoClicker.h"

AutoClicker::AutoClicker() : IModule(0, Category::COMBAT, "A simple autoclicker, automatically clicks for you.") {
	this->registerBoolSetting("rightclick", &this->rightclick, rightclick);
	this->registerBoolSetting("only weapons", &this->weapons, this->weapons);
	this->registerBoolSetting("break blocks", &this->breakBlocks, this->breakBlocks);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	this->registerBoolSetting("hold", &this->hold, this->hold);
}

AutoClicker::~AutoClicker() {
}

const char* AutoClicker::getModuleName() {
	return ("AutoClicker");
}

void AutoClicker::onTick(C_GameMode* gm) {
	if ((GameData::isLeftClickDown() || !hold)) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		Odelay++;

		if (Odelay >= delay) {
			auto selectedItem = localPlayer->getSelectedItem();
			if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
				return;

			g_Data.leftclickCount++;

			localPlayer->swingArm();

			if (pointing->hasEntity() != 0)
				g_Data.getCGameMode()->attack(pointing->getEntity());
			else if (breakBlocks) {
				bool isDestroyed = false;
				g_Data.getCGameMode()->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
				g_Data.getCGameMode()->stopDestroyBlock(pointing->block);
				if (isDestroyed && localPlayer->region->getBlock(pointing->block)->blockLegacy->blockId != 0)
					g_Data.getCGameMode()->destroyBlock(&pointing->block, 0);
			}
			Odelay = 0;
		}
	}
}
void AutoClicker::onLevelRender() {
	if (rightclick) {
		if ((GameData::isRightClickDown() || !hold)) {
			PointingStruct* pstruct = g_Data.getClientInstance()->getPointerStruct();
			Odelay++;
			if (Odelay >= delay) {
				g_Data.rightclickCount++;
				g_Data.getCGameMode()->buildBlock(new vec3_ti(pstruct->block), pstruct->blockSide);
				Odelay = 0;
			}
		}
	}
}