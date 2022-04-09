#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class InsideAura : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool pushm = false;
	bool sex = false;
	int delay1 = 2;
	int delay2 = 0;

public:
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	float unlimRange = 50000;
	bool unlim = false;

	InsideAura();
	~InsideAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
};
