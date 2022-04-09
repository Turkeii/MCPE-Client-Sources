#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class NightMode : public IModule {
public:
	float modifier = 0.5f;

	NightMode() : IModule(0x0, Category::VISUAL, "Darkens the environment"){
		
	};
	~NightMode(){};

	virtual const char* getModuleName() override {
		return "NightMode";
	}
};