#pragma once
#include "..\ModuleManager.h"
#include "Module.h"

class Speed : public IModule {
private:
	float height = 0.40f;
	int counter = 1;
	int lhtick = 0;
	bool preventKick = false;
	int groundTimer = 0;
	bool intersect = false;

public:
	int timer = 20;
	float speed = 0.325f;

	// Hive
	bool isOnGround = false;
	float hSpeed = 0.315;
	int hiveC = 1;

	Speed();
	~Speed();

	std::string name = "Speed";
	SettingEnum mode = this;

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};