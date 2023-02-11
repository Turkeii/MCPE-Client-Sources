#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class AutoTotem : public IModule {
private:
	bool force = false;
public:
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	AutoTotem();
};