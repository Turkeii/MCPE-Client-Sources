#include "NoJumpDelay.h"
#include "../ModuleManager.h"

//Credits eKowz
NoJumpDelay::NoJumpDelay() : IModule(0, Category::PLAYER, "No delay between jumps") {
	registerIntSetting("Delay", &tickTimer, tickTimer, 0, 10);
	registerIntSetting("Timer", &speedTimer, speedTimer, 1, 30);
	registerBoolSetting("Use Timer", &usetimer, usetimer);
	registerBoolSetting("Bypass", &bypass, bypass);
}
NoJumpDelay::~NoJumpDelay() {
}

void NoJumpDelay::onDisable() {
	moving = false;
	static auto timerMod = moduleMgr->getModule<Timer>();
	if (usetimer) {
		*g_Data.getClientInstance()->minecraft->timer = 20;
		if (timerwasenabled) {
			timerMod->setEnabled(true);
			timerwasenabled = false;
		}
	}
}

void NoJumpDelay::onTick(C_GameMode* gm) {
	if (!g_Data.canUseMoveKeys()) return;
	if (!g_Data.getLocalPlayer()->isAlive()) return;
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;
	static auto timerMod = moduleMgr->getModule<Timer>();
	auto blink = moduleMgr->getModule<Blink>();
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	if (!timerMod->isEnabled())
		*g_Data.getClientInstance()->minecraft->timer = 20;

	if (player->fallDistance >= 2) {
		moving = false;
	}

	if (g_Data.getLocalPlayer()->velocity.squaredxzlen() <= 0.001) {
		moving = false;
	}

	int bps = g_Data.getLocalPlayer()->getBlocksPerSecond();
	if (bypass && moving && bps >= 9) {
		if (!blink->isEnabled()) blink->setEnabled(true);
	}
	else {
		if (blink->isEnabled()) blink->setEnabled(false);
	}

	if (gm->player->onGround && g_Data.canUseMoveKeys() && GameData::isKeyDown(*input->spaceBarKey)) {
		tick++;
		if (tick >= tickTimer) {
			gm->player->jumpFromGround();
			tick = 0;
		}
	}
	if (!gm->player->onGround) {
		if (usetimer) {
			*g_Data.getClientInstance()->minecraft->timer = speedTimer;
		}
		if (gm->player->onGround) {
			if (timerMod->isEnabled()) {
				timerwasenabled = true;
				timerMod->setEnabled(false);
			}
		}
	}
}

void NoJumpDelay::onMove(C_MoveInputHandler* input) {
	moving = true;
}

const char* NoJumpDelay::getModuleName() {
	return "NoJumpDelay";
}