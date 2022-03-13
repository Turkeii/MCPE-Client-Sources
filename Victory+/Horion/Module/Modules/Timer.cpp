#include "Timer.h"

Timer::Timer() : IModule(0, Category::PLAYER, "Increase the ticks per second") {
	this->registerIntSetting("TPS", &this->timer, this->timer, 1, 500);
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
