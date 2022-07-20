#include "SafeSpeed.h"

SafeSpeed::SafeSpeed() : IModule(0, Category::MOVEMENT, "You can run faster on 2b2e") {
}

SafeSpeed::~SafeSpeed() {
}

const char* SafeSpeed::getModuleName() {
	return ("SafeSpeed");
}

void SafeSpeed::onTick(C_GameMode* gm) {
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
}

void SafeSpeed::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
}
