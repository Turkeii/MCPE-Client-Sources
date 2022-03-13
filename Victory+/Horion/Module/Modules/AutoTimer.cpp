#include "AutoTimer.h"

AutoTimer::AutoTimer() : IModule(0, Category::MISC, "2b2e antikick timer!?!?") {
	this->registerIntSetting("tps", &this->timer, this->timer, 0, 500);
}

AutoTimer::~AutoTimer() {
}

const char* AutoTimer::getModuleName() {
	return ("AutoTimer");
}

void AutoTimer::onTick(C_GameMode* gm) {
	this->delay++;
	if (delay == 0) {
		*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
	}
	if (delay == 1) {
		*g_Data.getClientInstance()->minecraft->timer = 20.f;
	}
		if (this->delay >= 2) {
			this->delay = 0;
			return;
		
	}
}

void AutoTimer::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}
