#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class ToggleSounds : public IModule {
public:
	ToggleSounds() : IModule(0x0, Category::HUD, "Play sounds when toggeling modules!"){};
	~ToggleSounds(){};

	virtual const char* getModuleName() override { return "ToggleSounds"; }
};
