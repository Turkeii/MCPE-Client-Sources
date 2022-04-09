#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Killaura : public IModule {
public:
	SettingEnum rots;
	SettingEnum targ;
	bool info = false;
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	int counter = 0;
	int targethud = 0;
	bool noSwing = false;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	bool targetListA = false;
	bool outline = true;
	vec2 joe;

	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
};