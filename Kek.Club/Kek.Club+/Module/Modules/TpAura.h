#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TPAura : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = false;
	bool noSilent = false;
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
	float healthcheck = 3.f;
	bool healthcheck1 = false;
	SettingEnum RotMode;
	SettingEnum HitMode;

	TPAura();
	~TPAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
};