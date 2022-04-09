#include "FallSave.h"
#include "../ModuleManager.h"

FallSave::FallSave() : IModule(0, Category::MISC, "Save yourself from falling!") {
	registerFloatSetting("FallDistance", &fDist, fDist, 3, 8);
	registerIntSetting("TimerValue", &timerVal, timerVal, 0, 15);
	registerBoolSetting("Timer", &useTimer, useTimer);
	registerBoolSetting("Jump", &useJump, useJump);
}
FallSave::~FallSave() {
}

const char* FallSave::getModuleName() {
	return "FallSave";
}

void FallSave::onDisable() {
	static auto timerMod = moduleMgr->getModule<Timer>();
	if (useTimer) {
		*g_Data.getClientInstance()->minecraft->timer = 20;
		if (timerWasEnabled) {
			timerMod->setEnabled(true);
			timerWasEnabled = false;
		}
	}
}

void FallSave::onEnable() {
}

void FallSave::onTick(C_GameMode* gm) {
	static auto timerMod = moduleMgr->getModule<Timer>();
	if (gm->player->onGround) {
		gm->player->fallDistance = 0;
		if (!timerMod->isEnabled())
		*g_Data.getClientInstance()->minecraft->timer = 20;
	}
	if (gm->player->fallDistance >= fDist) {
		if (useTimer) {
			if (timerMod->isEnabled()) {
				timerWasEnabled = true;
				timerMod->setEnabled(false);
			}
			*g_Data.getClientInstance()->minecraft->timer = timerVal;
		}
		if (useJump) gm->player->jumpFromGround();
	}
}
