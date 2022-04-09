#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class TimeChanger : public IModule {
public:
	float modifier = 0.5f;
	TimeChanger() : IModule(0x0, Category::VISUAL, "Changes the client-sided time.") {
		registerFloatSetting("modifier", &modifier, modifier, 0.1f, 1.f);
	};
	~TimeChanger(){};

	virtual const char* getModuleName() override {
		return "TimeChanger";
	}
};
