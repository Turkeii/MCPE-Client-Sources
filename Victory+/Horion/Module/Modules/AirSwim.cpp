#include "AirSwim.h"

AirSwim::AirSwim() : IModule(0, Category::MOVEMENT, "Swim even though your in air") {
}

AirSwim::~AirSwim() {
}

const char* AirSwim::getModuleName() {
	return ("AirSwim");
}

void AirSwim::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	g_Data.getLocalPlayer()->didEnterWaterBool = true;
}

void AirSwim::onTick(C_GameMode* gm) {
	g_Data.getLocalPlayer()->didEnterWaterBool = true;
	g_Data.getLocalPlayer()->doWaterSplashEffect();
}

void AirSwim::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	g_Data.getLocalPlayer()->didEnterWaterBool = false;
}