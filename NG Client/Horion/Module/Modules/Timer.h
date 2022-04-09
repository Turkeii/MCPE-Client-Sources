#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Timer : public IModule {
public:
	int timer = 50;

	Timer() : IModule(0x0, Category::PLAYER, "Increase the ticks per second") {
		registerIntSetting("ticks per second", &timer, timer, 0, 200);
	};
	~Timer(){};

	void onTick(C_GameMode* gm) {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
	}

	void onDisable() {
		g_Data.getClientInstance()->minecraft->setTimerSpeed(20.f);
	}

	virtual const char* getModuleName() override {
		return "Timer";
	}
};