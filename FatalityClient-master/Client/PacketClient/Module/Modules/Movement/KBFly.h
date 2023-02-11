#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class KBFly : public IModule {
private:
	float speedMod = 1;
	bool stop = true;
	float standVel = 0;
	float moveVel = 0;
	bool resetValues = false;
	bool vanf = false;
	bool keyPressed = false;
	float vanFYVel = 1;
	bool nostop = false;
	bool helper = false;
	bool turnOnGold = false;
	bool goldWasOn = false;
public:
	virtual void onTick(C_GameMode* gm);
	virtual const char* getModuleName();
	virtual void onDisable();
	virtual void onEnable();
	KBFly();
};
