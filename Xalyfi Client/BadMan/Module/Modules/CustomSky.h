#pragma once
#include "Module.h"
class CustomSky : public IModule {
public:
	float intensity = 0.01f;

	CustomSky();
	~CustomSky();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	static float red;
	static float green;
	static float blue;
	static bool custom;
};
