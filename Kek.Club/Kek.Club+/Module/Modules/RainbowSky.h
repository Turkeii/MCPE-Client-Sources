#pragma once
#include "Module.h"
class RainbowSky : public IModule {
public:
	static int rFloat;
	static int bFloat;
	static int gFloat;
	bool rainbow = false;
	RainbowSky();
	~RainbowSky();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
