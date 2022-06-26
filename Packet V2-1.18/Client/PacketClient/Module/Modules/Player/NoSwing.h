#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class NoSwing : public IModule {
public:
	virtual const char* getModuleName() override;
	NoSwing();
};
