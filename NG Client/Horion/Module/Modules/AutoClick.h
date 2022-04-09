#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AutoClick : public IModule {
public:
	int delay = 0;
	int Odelay = 0;
	bool weapons = true;
	bool breakBlocks = true;
	bool rightclick = false;
	bool hold = false;

	AutoClick() : IModule(0x0, Category::COMBAT, "A simple AutoClick, automatically clicks for you.") {
		registerBoolSetting("rightclick", &rightclick, rightclick);
		registerBoolSetting("only weapons", &weapons, weapons);
		registerBoolSetting("break blocks", &breakBlocks, breakBlocks);
		registerIntSetting("delay", &delay, delay, 0, 20);
		registerBoolSetting("hold", &hold, hold);
	 };
	~AutoClick(){};

	virtual void onTick(C_GameMode* gm) {
		if ((GameData::isLeftClickDown() || !hold)) {
			C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
			PointingStruct* pointing = g_Data.getLocalPlayer()->pointingStruct;
			Odelay++;

			if (Odelay >= delay) {
				auto selectedItem = localPlayer->getSelectedItem();
				if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
					return;
				if (!rightclick) {
					if (pointing->hasEntity()) {
						g_Data.leftclickCount++;
						localPlayer->swingArm();
						gm->attack(pointing->getEntity());
					} else if (breakBlocks) {
						bool isDestroyed = false;
						localPlayer->swingArm();
						g_Data.leftclickCount++;
						gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
						if (isDestroyed && localPlayer->region->getBlock(pointing->block)->blockLegacy->blockId != 0)
							gm->destroyBlock(&pointing->block, pointing->blockSide);
						if (isDestroyed)
							gm->stopDestroyBlock(pointing->block);
					}
					Odelay = 0;
				}
			}
		}
	}
	virtual void onLevelRender() {
		if (rightclick) {
			if ((GameData::isRightClickDown() || !hold) && g_Data.isInGame()) {
				PointingStruct* pstruct = g_Data.getLocalPlayer()->pointingStruct;
				auto gm = g_Data.getCGameMode();
				Odelay++;
				if (Odelay >= delay) {
					g_Data.rightclickCount++;
					C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
					localPlayer->swingArm();
					gm->startBuildBlock(vec3i(pstruct->block), pstruct->blockSide);
					gm->stopBuildBlock();
					gm->buildBlock(new vec3i(pstruct->block), pstruct->blockSide);
					Odelay = 0;
				}
			}
		}
	}

	virtual const char* getModuleName() override {
		return "AutoClick";
	}
};