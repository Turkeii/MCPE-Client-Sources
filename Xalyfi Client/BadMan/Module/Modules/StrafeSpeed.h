#pragma once
#include "Module.h"
class StrafeSpeed : public IModule {
private:
	float nspeed = 0.30f;
	float jspeed = 0.17f;
	float lspeed = 0.225f;
	float wspeed = 0.225f;
	float jsspeed = 0.13f;
	float sspeed = 0.10f;

	bool sprint = false;
	bool keyPressed = false;

public:
	StrafeSpeed();
	~StrafeSpeed();

	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};
