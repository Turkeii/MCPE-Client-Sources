#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class InsideTP : public IModule {
private:
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	bool silent = true;
	bool pushm = false;
	bool Kill = false;
	bool Killmob = false;

public:
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	float unlimRange = 50000;
	bool unlim = false;

	InsideTP();
	~InsideTP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override;
};
