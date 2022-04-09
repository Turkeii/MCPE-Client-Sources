#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class FastLadder : public IModule {
public:
	float speed = 0.6f;

	FastLadder() : IModule(0x0, Category::MOVEMENT, "Climb up ladders faster") {
		registerFloatSetting("Speed", &speed, speed, 0.1f, 1.0f);
	};
	~FastLadder(){};

	virtual const char* getModuleName() override {
		return "FastLadder";
	}
};