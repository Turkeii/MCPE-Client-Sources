#pragma once
#include "Module.h"
class NoMiningTrace : public IModule {
public:
	NoMiningTrace();
	~NoMiningTrace();
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
