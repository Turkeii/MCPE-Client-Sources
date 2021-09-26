#pragma once
#include "Module.h"
class Teleport : public IModule {
private:

public:
	Teleport();
	~Teleport();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};