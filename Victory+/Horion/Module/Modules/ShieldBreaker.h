#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class ShieldBreak : public IModule {
private:
	bool isMulti = true;
	int delay = 0;
	int Odelay = 0;

public:
	bool isPlayerAura = true;
	bool isMobAura = false;
	bool hurttime = false;
	float range = 6;

	ShieldBreak();
	~ShieldBreak();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};