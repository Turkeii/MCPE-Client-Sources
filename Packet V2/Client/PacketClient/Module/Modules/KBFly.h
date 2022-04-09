#pragma once
#include "Module.h"
#include "../ModuleManager.h"

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
	KBFly();
	~KBFly();

	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	// Inherited via IModule
	virtual const char* getModuleName() override;
};
