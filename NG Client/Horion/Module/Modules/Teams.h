#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Teams : public IModule {
public:
	bool alliedCheck = false;
	bool colorCheck = true;

	Teams() : IModule(0x0, Category::COMBAT, "DOSENT WORK!!!") {
		registerBoolSetting("is allied", &alliedCheck, alliedCheck);
		registerBoolSetting("same color", &colorCheck, colorCheck);
	};
	bool isAlliedCheckEnabled() { return isEnabled() && alliedCheck; };
	bool isColorCheckEnabled() { return isEnabled() && colorCheck; };
	~Teams(){};

	virtual const char* getModuleName() override {
		return "Teams";
	}
};