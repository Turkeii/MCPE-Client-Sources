#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class TimeChanger : public IModule {
public:
	float modifier = 1.f;

	TimeChanger();
	~TimeChanger();

	std::string name = ("TimeChanger");

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getRawModuleName() override;
};