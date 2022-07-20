#pragma once
#include "Module.h"
#include "../ModuleManager.h"
#include "../../../Utils/Target.h"

class Killaura : public IModule
{
private:
	bool isMulti = true;
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = false;
	bool noSilent = false;
	bool VisTarget = false;

	SettingEnum RotMode;

public:
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	int timer5 = 0;


	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onLevelRender() override;
};

