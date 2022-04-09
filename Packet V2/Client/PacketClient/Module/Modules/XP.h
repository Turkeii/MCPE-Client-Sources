#pragma once

#include "Module.h"

class XP : public IModule {
private:
	bool levels = true;
	int amount = 1;

public:
	XP();

	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
};