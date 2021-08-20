#pragma once
#include "Module.h"
class Logs : public IModule {
public:
	Logs();
	~Logs();
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
