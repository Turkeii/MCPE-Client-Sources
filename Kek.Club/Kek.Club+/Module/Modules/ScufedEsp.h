#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class ScufedEsp : public IModule {
public:
	SettingEnum type{this};
	ScufedEsp();
	~ScufedEsp();
	// Inherited via IModule
	virtual const char* getModuleName() override;
};