#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class JavaAura : public IModule {
private:
	bool isMulti = false;
	bool rot = false;
	int delay = 16;
	int Odelay = 0;

public:
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;

	JavaAura();
	~JavaAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual const char* getRawModuleName() override;
};
