#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AirSwim : public IModule {
public:
	bool particles = true;

	AirSwim() : IModule(0x0, Category::MOVEMENT, "Swim even though your in air") {
		registerBoolSetting("Particles", &particles, particles);
	};
	~AirSwim(){};

	void onEnable() {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr)
			return;
		player->didEnterWaterBool = true;
		player->startSwimming();
	}

	void onTick(C_GameMode* gm) {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		player->didEnterWaterBool = true;
		if (particles)
			player->doWaterSplashEffect();
		player->startSwimming();
	}

	void onDisable() {
		C_LocalPlayer* player = g_Data.getLocalPlayer();
		if (player == nullptr)
			return;
		player->didEnterWaterBool = false;
		player->stopSwimming();
	}

	virtual const char* getModuleName() override {
		return "AirSwim";
	}
};