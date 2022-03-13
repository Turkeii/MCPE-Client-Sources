#include "SpeedBypass.h"

#include "../../DrawUtils.h"

SpeedBypass::SpeedBypass() : IModule(0, Category::MOVEMENT, "Bypass Speed up!! BY giyo & Kaeru") {
	this->registerIntSetting("Speed", &this->timer, this->timer, 20, 500);
	registerBoolSetting("Endzone", &this->endzone, this->endzone);
	//registerBoolSetting("2B2E", &this->Bypass, this->Bypass);
}

SpeedBypass::~SpeedBypass() {
}

const char* SpeedBypass::getModuleName() {
		return ("SpeedBypass");
}

const char* SpeedBypass::getRawModuleName() {
	return "SpeedBypass";
}

void SpeedBypass::onTick(C_GameMode* gm) {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (endzone) {
		Odelay++;
		if (Odelay == 10) timer = 20;
		if (Odelay == 20) timer = 30;
		if (Odelay == 30) timer = 40;
		if (Odelay == 40) timer = 50;
		if (Odelay == 50) timer = 60;
		if (Odelay == 60) Odelay = 0;
	}

		if (Bypass) {
		Odelay++;
		if (Odelay == 20) timer = 20;
		if (Odelay == 50) timer = 200;

		if (Odelay == 70) Odelay = 0;
	}
		if (Bypass) {
			bool endzone = false;
		}
		if (endzone) {
			bool Bypass = false;
		}
	vec3_t floorPos = *g_Data.getLocalPlayer()->getPos();
	floorPos.y = g_Data.getLocalPlayer()->getAABB()->lower.y + 0.2f;

	if (!stopBreadCrums)
		linePoints.push_back(floorPos);
	*g_Data.getClientInstance()->minecraft->timer = static_cast<float>(this->timer);
}

void SpeedBypass::onLevelRender() {
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (!linePoints.empty()) {
		DrawUtils::setColor(1.f, 1.f, 1.f, 1.f);
		DrawUtils::drawLinestrip3d(linePoints);
	}
}

void SpeedBypass::onDisable() {
	*g_Data.getClientInstance()->minecraft->timer = 20.f;
	auto player = g_Data.getLocalPlayer();
	if (player == nullptr) return;

	if (clearOndisable)
		linePoints.clear();
}