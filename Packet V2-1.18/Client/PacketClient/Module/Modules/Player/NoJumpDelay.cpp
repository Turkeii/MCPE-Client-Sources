#include "NoJumpDelay.h"
#include "../pch.h"

//Credits eKowz
NoJumpDelay::NoJumpDelay() : IModule(0, Category::PLAYER, "Changes the delay between jumps") {
	registerBoolSetting("Blink", &bypass, bypass);
	registerIntSetting("Delay", &tickTimer, tickTimer, 0, 10);
	registerIntSetting("Timer", &timer, timer, 1, 80);
}

const char* NoJumpDelay::getModuleName() {
	return "NoJumpDelay";
}

void NoJumpDelay::onTick(C_GameMode* gm) {
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();
	static auto timerMod = moduleMgr->getModule<Timer>();
	auto blink = moduleMgr->getModule<Blink>();
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	int bps = g_Data.getLocalPlayer()->getBlocksPerSecond();
	if (!timerMod->isEnabled())
		*g_Data.getClientInstance()->minecraft->timer = 20;

	if (g_Data.getLocalPlayer()->velocity.squaredxzlen() <= 0.001 || player->fallDistance >= 2)
		moving = false;

	// bro
	if (bypass && moving && bps >= 9) if (!blink->isEnabled()) blink->setEnabled(true);
	else if (blink->isEnabled()) blink->setEnabled(false);

	if (gm->player->onGround && g_Data.canUseMoveKeys() && GameData::isKeyDown(*input->spaceBarKey)) {
		tick++;
		if (tick >= tickTimer) {
			gm->player->jumpFromGround();
			tick = 0;
		}
	}

	if (!gm->player->onGround) {
		*g_Data.getClientInstance()->minecraft->timer = timer;
		if (gm->player->onGround) {
			if (timerMod->isEnabled()) {
				timerwasenabled = true;
				timerMod->setEnabled(false);
			}
		}
	}
}

void NoJumpDelay::onMove(C_MoveInputHandler* input) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	moving = true;
}

void NoJumpDelay::onDisable() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	moving = false;
	static auto timerMod = moduleMgr->getModule<Timer>();
	*g_Data.getClientInstance()->minecraft->timer = 20;
	if (timerwasenabled) {
		timerMod->setEnabled(true);
		timerwasenabled = false;
	}
}