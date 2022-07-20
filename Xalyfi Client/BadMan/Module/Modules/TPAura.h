#pragma once
#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/Target.h"

class TPAura : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = true;
	int delay1 = 0;
	int delay2 = 0;
	int turn = 0;

public:
	bool isMobAura = false;
	float range = 6;
	float unlimRange = 50000;
	bool unlim = false;
	bool lerp = false;
	bool isMulti = true;

	TPAura();
	~TPAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
};

