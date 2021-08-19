#pragma once

#include "Module.h"

class NoFall : public IModule {
public:
	bool motionMode = false;

	NoFall();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
};