#pragma once
#include "Module.h"
class FullBright : public IModule {
public:

	FullBright();
	~FullBright();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
