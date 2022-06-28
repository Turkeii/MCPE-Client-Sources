#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Killaura : public IModule {
private:
	bool multi = true;
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = false;
	bool noSilent = false;
	bool Client = false;
	bool VisTarget = false;

public:
	SettingEnum BlockMode;
	SettingEnum RotMode;
	SettingEnum HitMode;
	SettingEnum priority;
	bool isMobAura = false;
	bool noSwing = false;
	bool hurttime = true;
	float range = 6;
	int timer5 = 0;
	float healthcheck = 3.f;
	bool healthcheck1 = false;
	bool targetListA = false;
	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onLevelRender() override;
};