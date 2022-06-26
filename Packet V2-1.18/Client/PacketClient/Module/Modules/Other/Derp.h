#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"
class Derp : public IModule {
private:
	bool headless = false;
	bool silent = false;
	bool twerk = false;
	float speed = 1.f;
	bool spin = true;
	int delay = 1;
	int tick = 0;

public:
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onPlayerTick(C_Player* plr) override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	Derp();
};
