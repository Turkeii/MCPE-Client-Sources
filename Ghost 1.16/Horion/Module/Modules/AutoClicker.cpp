#include "AutoClicker.h"

AutoClicker::AutoClicker() : IModule(0, Category::COMBAT, "A simple autoclicker, automatically clicks for you.") {
	this->registerBoolSetting("rightclick", &this->rightclick, rightclick);
	this->registerBoolSetting("only weapons", &this->weapons, this->weapons);
	this->registerBoolSetting("break blocks", &this->breakBlocks, this->breakBlocks);
	this->registerIntSetting("delay", &this->delay, this->delay, 0, 20);
	this->registerBoolSetting("hold", &this->hold, this->hold);

	this->registerBoolSetting("jitter", &this->jitter, this->jitter);
	this->registerIntSetting("yJitter", &this->xJitter, this->xJitter, 0, 15);
	this->registerIntSetting("xJitter", &this->yJitter, this->yJitter, 0, 15);

	this->registerBoolSetting("randomDelay", &this->doRand, this->doRand);
	this->registerIntSetting("minRand", &this->minRand, this->minRand, 1, 20);
	this->registerIntSetting("maxRand", &this->maxRand, this->maxRand, 1, 20);
}

float RandomInt(int min, int max) {
	float r = (int)rand() / (int)RAND_MAX;
	return min + r * (max - min);
}

AutoClicker::~AutoClicker() {
}

const char* AutoClicker::getModuleName() {
	return ("AutoClicker");
}

int actualDelay;
bool hasRand = false;

void AutoClicker::onTick(C_GameMode* gm) {
	if (hasRand != true)
		if (doRand) {
			//actualDelay = (float)(rand() % (2 * xJitter + 1) + (-xJitter));
			actualDelay = (int)(rand() % ((maxRand - minRand) + minRand));  //is in the range 1 to 100

			hasRand = true;

		} else {
			actualDelay = delay;
		}

	if (actualDelay == NULL) actualDelay = delay;

	if ((GameData::isLeftClickDown() || !hold) && GameData::canUseMoveKeys()) {
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		PointingStruct* pointing = g_Data.getClientInstance()->getPointerStruct();
		Odelay++;

		if (Odelay >= actualDelay) {
			auto selectedItemId = localPlayer->getSelectedItemId();

			if (jitter)
				g_Data.getLocalPlayer()->applyTurnDelta(&vec2_t((float)(rand() % (2 * xJitter + 1) + (-xJitter)), (float)(rand() % (2 * yJitter + 1) + (-yJitter))));
			if (!moduleMgr->getModule<NoSwing>()->isEnabled())
				localPlayer->swingArm();

			if (pointing->entityPtr != 0)
				gm->attack(pointing->entityPtr);

			else if (breakBlocks) {
				bool isDestroyed = false;
				gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
				gm->stopDestroyBlock(pointing->block);
				if (isDestroyed && localPlayer->region->getBlock(pointing->block)->blockLegacy->blockId != 0)
					gm->destroyBlock(&pointing->block, 0);
			}
			hasRand = false;
			Odelay = 0;
		}
	}

	if (rightclick) {
		if ((GameData::isRightClickDown() || !hold) && GameData::canUseMoveKeys()) {
			PointingStruct* pstruct = g_Data.getClientInstance()->getPointerStruct();
			Odelay++;
			if (Odelay >= delay) {
				g_Data.rightclickCount++;
				gm->buildBlock(new vec3_ti(pstruct->block), pstruct->blockSide);
				Odelay = 0;
			}
		}
	}
}