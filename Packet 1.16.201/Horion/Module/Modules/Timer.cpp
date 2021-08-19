#include "Timer.h"

Timer::Timer() : IModule(0, Category::MISC, "Increases/Decreases Client TPS. Bypasses most servers.") {
	this->registerIntSetting("TPS", &this->timer, this->timer, 5, 700);
}

Timer::~Timer() {
}

const char* Timer::getModuleName() {
	return ("Timer");
}

void Timer::onTick(C_GameMode* gm) {
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
}

void Timer::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}