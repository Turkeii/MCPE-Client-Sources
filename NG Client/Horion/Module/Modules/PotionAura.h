#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class PotionAura : public IModule {
private:
	bool info = false;
	int delay = 0;
	int Odelay = 0;
	bool autoweapon = false;
	void findWeapon();
	bool silent = false;

public:
	bool rotations = true;
	bool isMulti = true;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 6;
	bool targetListA = false;
	bool sexy = true;
	bool outline = true;
	vec2 joe;

	PotionAura();
	~PotionAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onLevelRender() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onPostRender(C_MinecraftUIRenderContext* ctx) override;
};