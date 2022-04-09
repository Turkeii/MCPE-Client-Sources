#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class TPAura : public IModule {
public:
	void findWeapon();

	bool autoweapon = false;
	bool TPAuratargetHUD = true;
	bool hurttime = true;
	bool unlim = false;
	bool lerp = false;
	bool isMulti = true;
	bool isMobAura = false;

	float range = 6;
	float unlimRange = 50000;

	int delay = 0;
	int Odelay = 0;
	int delay1 = 0;
	int delay2 = 0;
	int turn = 0;

	TPAura();
	~TPAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* ctx) override;
};
