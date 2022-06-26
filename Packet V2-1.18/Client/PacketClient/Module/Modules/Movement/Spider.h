#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Spider : public IModule {
private:
	bool dontOvershoot = true;
	float speed = 0.6f;
public:
	virtual void onMove(C_MoveInputHandler* input);
	virtual const char* getModuleName();
	Spider();
};