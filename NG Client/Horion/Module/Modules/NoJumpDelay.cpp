#include "NoJumpDelay.h"
#include "../ModuleManager.h"

NoJumpDelay::NoJumpDelay() : IModule(0, Category::PLAYER, "No delay between jumps") {
	registerIntSetting("Delay", &tickTimer, tickTimer, 0, 10);
	registerIntSetting("Timer", &speedTimer, speedTimer, 1, 30);
	registerFloatSetting("VelY", &heightY, heightY, 1.00f, 1.03f);
	registerFloatSetting("VelXZ", &xyzvel, xyzvel, 1.00f, 1.03f);
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
	if (bypass && moving && bps >= 8) {
		if (!blink->isEnabled()) blink->setEnabled(true);
		gm->player->velocity.y *= heightY;
		gm->player->velocity.x *= xyzvel;
		gm->player->velocity.z *= xyzvel;
	} else {
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