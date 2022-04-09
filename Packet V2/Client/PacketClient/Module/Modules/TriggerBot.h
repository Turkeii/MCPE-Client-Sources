#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class TriggerBot : public IModule {
private:
	bool hurttime = false;
	int delay = 0;
	int Odelay = 0;

public:
	float range = 8;
	TriggerBot();
	~TriggerBot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
