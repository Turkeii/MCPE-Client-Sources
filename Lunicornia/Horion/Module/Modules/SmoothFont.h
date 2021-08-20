#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class SmoothFont : public IModule
{
public:
	SmoothFont() : IModule(0x0, Category::VISUAL, "When enabled, removed the default Minecraft font.") {}
	~SmoothFont() {}

	// Inherited via IModule
	virtual const char* getModuleName() override
	{
		return ("SmoothFont");
	}
};