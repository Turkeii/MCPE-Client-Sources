#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class SafeWalk : public IModule {
public: 
	virtual const char* getModuleName();
	SafeWalk();
};