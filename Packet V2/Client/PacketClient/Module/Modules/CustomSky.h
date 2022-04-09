#pragma once

#include "Module.h"

class CustomSky : public IModule {
public:
	bool rainbow = false;
	float red = 0.f;
	float green = 0.f;
	float blue = 0.f;

	CustomSky();
	virtual const char* getModuleName();
};