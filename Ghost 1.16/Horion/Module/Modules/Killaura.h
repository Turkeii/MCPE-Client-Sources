#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Killaura : public IModule {
private:
	bool isMulti = true;
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool yeet = false;
	bool head = true;
	bool body = true;
	bool extra = true;
	//bool crit = false;

	public:
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;

	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
