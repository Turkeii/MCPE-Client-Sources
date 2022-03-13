#pragma once
#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/Target.h"

class Killaura : public IModule
{
private:
	bool isMulti = true;
	bool rot = false;
	int delay = 0;
	int Odelay = 0;
	bool SilentAttack = false;

public:
	bool isMobAura = false;
	bool hurttime = false;
	float range = 6;
	int timer5 = 0;
	int timer = 0;
	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	//virtual void onDisable() override;
	virtual void onLevelRender() override;
	virtual const char* getRawModuleName() override;
};

