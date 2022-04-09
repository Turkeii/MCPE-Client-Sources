#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AntiLagBack : public IModule {
public:

	AntiLagBack() : IModule(0x0, Category::PLAYER, "Changes the client-sided time."){};
	~AntiLagBack(){};

	virtual const char* getModuleName() override {
		return "AntiLagBack";
	}
};
