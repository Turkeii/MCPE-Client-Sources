#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class InfiniteAura : public IModule {
private:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;

	int delay = 15;
	int Odelay = 0;
	bool isMulti = false;

public:
	bool targetListC = false;
	bool sex = false;
	vec2 amogus;
	bool packetfukery;
	bool isMobAura = false;
	bool hivee = false;
	bool treas = false;
	float range = 15;
	int counter = 1;
	InfiniteAura();
	~InfiniteAura();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override;

	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};