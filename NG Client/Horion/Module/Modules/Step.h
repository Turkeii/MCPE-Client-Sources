#pragma once
#include "Module.h"
class Step : public IModule {
public:
	float height = 2.f;

	Step() : IModule(0x0, Category::MOVEMENT, "Increases your step height") {
		registerFloatSetting("height", &height, height, 1.f, 2.f);
	}
	~Step(){}

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("Step"); }
	virtual void onTick(C_GameMode* gm) override { gm->player->stepHeight = height; }
	virtual void onDisable() override {
		if (g_Data.getLocalPlayer() != nullptr)
			g_Data.getLocalPlayer()->stepHeight = 0.5625f;
	}
};