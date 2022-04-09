#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class HighJump : public IModule {
public:
	float jumpPower = 1.8f;

	HighJump() : IModule(0x0, Category::MOVEMENT, "Jump higher than ever before") {
		registerFloatSetting("Jump Height", &jumpPower, 1, 0.00f, 5.00f);
	};

	~HighJump(){};

	virtual const char* getModuleName() override {
		return "HighJump";
	}
};
