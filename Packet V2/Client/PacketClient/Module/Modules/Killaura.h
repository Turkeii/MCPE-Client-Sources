#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class Killaura : public IModule {
private:
	bool test = false;

public:
	bool targetListEmpty = true; // shouldBlock
	bool visualize = true;
	bool strafe = false;
	bool multi = false;
	bool click = false;
	bool hold = false;
	bool mobs = false;
	float range = 8.f;
	int maxAPS = 20;
	int minAPS = 20;

	// Rotations
	vec2_t theRot;

	std::string name = "Killaura";
	SettingEnum mode = this;

	Killaura();
	~Killaura();

	// Inherited via IModule
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onPlayerTick(C_Player* plr) override;
};