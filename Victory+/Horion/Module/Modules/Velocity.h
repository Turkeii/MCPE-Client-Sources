#pragma once

#include "Module.h"

class Velocity : public IModule {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;
	float x;
	float y;  
		bool pa = "%";

	Velocity();
	~Velocity();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
};
