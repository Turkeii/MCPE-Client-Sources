#pragma once

#include "Module.h"

class TPAura : public IModule {
private:
	int delay = 0;

public:
	TPAura();
	virtual const char* getModuleName();
};