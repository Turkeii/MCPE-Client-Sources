#include "Jazzing.h"

Jazzing::Jazzing() : IModule(0, Category::BLATANT, "Start jazzing around") {
}

Jazzing::~Jazzing() {
}

const char* Jazzing::getModuleName() {
	return ("Jazzing");
}

void Jazzing::onEnable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	g_Data.getLocalPlayer()->didEnterWaterBool = true;
	g_Data.getLocalPlayer()->startSwimming();
}

void Jazzing::onTick(C_GameMode* gm) {
	g_Data.getLocalPlayer()->didEnterWaterBool = true;
	g_Data.getLocalPlayer()->doWaterSplashEffect();
	g_Data.getLocalPlayer()->startSwimming();
}

void Jazzing::onDisable() {
	if (g_Data.getLocalPlayer() == nullptr)
		return;
	g_Data.getLocalPlayer()->didEnterWaterBool = false;
	g_Data.getLocalPlayer()->stopSwimming();
}