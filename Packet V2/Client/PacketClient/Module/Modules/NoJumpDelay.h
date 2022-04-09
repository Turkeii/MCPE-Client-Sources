#pragma once
#include "Module.h"

class NoJumpDelay : public IModule {
public:
	NoJumpDelay();
	~NoJumpDelay();
	int tick = 0;
	int tickTimer = 0;
	int speedTimer = 20;
	bool bypass = false;
	bool moving = false;
	bool usetimer = false;
	bool timerwasenabled = false;

	virtual void onTick(C_GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onDisable() override;
	const char* getModuleName() override;
};