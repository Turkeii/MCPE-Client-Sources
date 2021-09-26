#pragma once

#include "Module.h"

class Disabler : public IModule {
public: 
	bool hive = true;
	bool elytra = false;
	bool air = false;
	float speed = 1.f;
	float glideMod = 0.f;
	float glideModEffective = 0;
	int counter = 1;
    Disabler();
    virtual const char* getModuleName();
	virtual void onMove(C_MoveInputHandler* input) override;
	void onTick(C_GameMode* gm);
	void onSendPacket(C_Packet* packet) override;
	//virtual void onSendPacket(C_Packet* packet) override;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
};