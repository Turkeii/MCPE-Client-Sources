#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Zoom : public IModule {
public:
	float strength = 0.5f;

	Zoom() : IModule(0x0, Category::VISUAL, "Modifies your FOV") {
		registerFloatSetting("Strength", &strength, strength, 0.f, 1.f);
	};

	bool Zoom::isHoldMode() {
		return true;
	}
	void onLevelRender() {
		if (g_Data.getLocalPlayer() != nullptr && g_Data.isInGame())
			g_Data.getLocalPlayer()->setFieldOfViewModifier(strength);
	}
	void onDisable() {
		g_Data.getLocalPlayer()->setFieldOfViewModifier(1.0f);
	}
	virtual const char* getModuleName() override {
		return "Zoom";
	}
};