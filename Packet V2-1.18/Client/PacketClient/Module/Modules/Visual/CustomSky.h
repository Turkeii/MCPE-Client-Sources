#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class CustomSky : public IModule {
public:
	float red = 1.f, green = 1.f, blue = 1.f;
	bool rainbow = false;

	virtual const char* getModuleName();
	CustomSky();
};