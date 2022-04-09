#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Camera : public IModule {
public:
	float intensity = 25.f;
	float* gammaPtr = nullptr;
	bool nohurtcam = false;

	Camera() : IModule(0x0, Category::VISUAL, "Puts your gamma to max") {
		registerFloatSetting("Intensity", &intensity, intensity, -25.f, 25.f);
		registerBoolSetting("NoHurtcam", &nohurtcam, nohurtcam);
	};
	~Camera(){};

	float originalGamma = -1;

	void onWorldTick(C_GameMode* gm) {
		if (nohurtcam) {
		g_Data.getLocalPlayer()->cancelHurtAnimation();
		}
	}

	void onTick(C_GameMode* gm) {
		if (gammaPtr != nullptr && *gammaPtr != 10)
			*gammaPtr = 10;
	}

	void onEnable() {
		if (gammaPtr != nullptr) {
			originalGamma = *gammaPtr;
			*gammaPtr = 10;
		}
	}

	void onDisable() {
		if (gammaPtr != nullptr) {
			if (originalGamma >= 0 && originalGamma <= 1)
				*gammaPtr = originalGamma;
			else
				*gammaPtr = 0.5f;
		}
	}

	virtual const char* getModuleName() override {
		return "Camera";
	}
};