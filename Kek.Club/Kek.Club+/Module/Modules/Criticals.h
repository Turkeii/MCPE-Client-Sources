#pragma once
#include "Module.h"
#include "../ModuleManager.h"
class Criticals : public IModule {
private:
	bool packets = true;
	bool noFallWasEnabled = false;

public:
	Criticals();
	~Criticals();
	SettingEnum mode;
	static int constexpr Packet_mode = 0;
	static int constexpr Vanilla_mode = 1;

	// Inherited via IModule
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onAttack(C_Entity* attackedEnt);
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getModName() override;
};
