#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Zoom : public IModule {
public:
	float strength = 0.5f;
	float OGFov;

	Zoom() : IModule(0x0, Category::VISUAL, "Zoom in or out!") {
		registerFloatSetting("Strength", &strength, strength, 0.f, 1.f);
	};
	~Zoom(){};

	void onEnable() {
	}
	void onPlayerTick(C_Player* e) {
		if (g_Data.getLocalPlayer() != nullptr && g_Data.isInGame())
			g_Data.getLocalPlayer()->setFieldOfViewModifier(strength);
	}
	void onDisable() {
		g_Data.getLocalPlayer()->setFieldOfViewModifier(OGFov);
	}
	virtual const char* getModuleName() override {
		return "Zoom";
	}
};