#pragma once
#include "Module.h"
class NoSwing : public IModule {
public:
	NoSwing() : IModule(0x0, Category::PLAYER, "Disable arm swing animation") {}
	~NoSwing(){};

	// Inherited via IModule
	virtual const char* getModuleName() override { return ("NoSwing"); }
};
