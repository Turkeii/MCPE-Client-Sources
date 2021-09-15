#include "SlowDown.h"

SlowDown::SlowDown() : IModule(0, Category::MISC, "Makes you go slowwwwwww") {
	this->registerIntSetting("ticks per second", &this->timer, this->timer, 3, 15);
}

SlowDown::~SlowDown() {
}

const char* SlowDown::getModuleName() {
	return ("SlowDown");
}

void SlowDown::onTick(C_GameMode* gm) {
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
}

void SlowDown::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}
