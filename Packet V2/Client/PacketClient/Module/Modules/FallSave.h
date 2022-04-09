#pragma once
#include "Module.h"

class FallSave : public IModule {
private:
	float fDist = 3;
	int timerVal = 15;
	bool useTimer = true;
	bool useJump = false;
	bool timerWasEnabled = false;

public:
	FallSave();
	~FallSave();

	const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
};
