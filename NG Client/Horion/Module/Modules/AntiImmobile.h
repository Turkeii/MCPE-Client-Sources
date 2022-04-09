#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AntiImmobile : public IModule {
public:

	AntiImmobile() : IModule(0x0, Category::MOVEMENT, "Disables immobile flag set by some servers to prevent you from moving"){
	};
	~AntiImmobile(){};

	virtual const char* getModuleName() override {
		return "AntiImmobile";
	}
};
