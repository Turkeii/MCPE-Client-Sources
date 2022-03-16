#pragma once

#include "Module.h"

class LongJump : public IModule {
private:
	float glideMod = -0.16f;
	bool dmgMode = true;
	float tpDis = 0.f;
	bool slowDown = true;
	bool floatMode = false;
	float glideModEffective = 0;
	float height = 1.f;
	int testTimer = 0;
	float speed = 2.f;
	// int timer = 10;
	// bool timerMode = false;
	bool lowMode = true;

public:
	LongJump();
	// virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};