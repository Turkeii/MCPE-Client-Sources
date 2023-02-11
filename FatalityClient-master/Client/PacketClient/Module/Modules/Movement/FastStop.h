#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class FastStop : public IModule {
public:
	virtual void onMove(C_MoveInputHandler* input);
	virtual const char* getModuleName();
	FastStop();
};