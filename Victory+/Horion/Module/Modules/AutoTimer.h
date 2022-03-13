#pragma once
#include "Module.h"
class AutoTimer : public IModule {
private:
	int timer = 50;
	float delay = 0.f;

public:
	AutoTimer();
	~AutoTimer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
};
