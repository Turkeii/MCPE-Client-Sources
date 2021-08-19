#pragma once

#include "Module.h"

class AutoPlay : public IModule {
public:
	bool hiveMode = false;

	AutoPlay();
	virtual const char* getModuleName();
};