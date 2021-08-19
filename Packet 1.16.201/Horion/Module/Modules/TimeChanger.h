#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class TimeChanger : public IModule {
public:
	TimeChanger();
	~TimeChanger();

	float modifier = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
