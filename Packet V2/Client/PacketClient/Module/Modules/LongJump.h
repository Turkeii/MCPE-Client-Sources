#pragma once

#include "Module.h"

class LongJump : public IModule {
private:
	float glideMod = -0.16f;
	int counter = 1;
	int counter2 = 0;
	bool damage = false;
	bool slowDown = true;
	bool old = false;
	float height = 1.f;
	float speed = 2.f;

		SettingEnum mode = this;

public:
	LongJump();
	//virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};