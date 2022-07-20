#include "Timer.h"
#include "../ModuleManager.h"

Timer::Timer() : IModule(0, Category::PLAYER, "Increase the ticks per second") {
	this->registerIntSetting("TPS", &this->timer, this->timer, 1, 500);
	registerBoolSetting("Bypass", &this->bypass, this->bypass);
}

Timer::~Timer() {
}

const char* Timer::getModuleName() {
	return ("Timer");
}

void Timer::onTick(C_GameMode* gm) {
	static auto blinkMod = moduleMgr->getModule<Blink>();
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
	if (bypass) {
		blinkMod->setEnabled(true);
	}
}

void Timer::onDisable() {
	static auto blinkMod = moduleMgr->getModule<Blink>();
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	blinkMod->setEnabled(false);
}
