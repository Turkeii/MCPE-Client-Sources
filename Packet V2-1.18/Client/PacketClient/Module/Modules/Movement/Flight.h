#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class Flight : public IModule {
private:
	bool speedWasEnabled = false;
	float speedDuration = 1.f;
	bool hasJumped = false;
	float currSpeed = 1.f;
	int enabledHeight = 0;
	float duration = 1.f;
	bool damage = false;
	bool boost = false;
	int currHeight = 0;
	int jumpTick = 0;
	int tick = 0;

public:
	bool viewBobbingEffective = false;
	float effectiveValue = 0.f;
	bool viewBobbing = true;
	float testfloat = 0;
	float value = 0.f;
	float speed = 1.f;
	int timerVariable = 5;

	// Hive
	bool velocityEffective = false;
	bool shouldFly = false;
	int hiveSpeedIndex = 0;
	int hiveVelocity = 0;
	int enabledTick = 0;
	int hiveTick = 0;
	int dmgTick = 0;
	vec3_t initPos;

	std::string name = "Flight";
	C_MovePlayerPacket* jetpack = nullptr;
	SettingEnum mode = this;

	// Inherited via IModule
	virtual void onMove(C_MoveInputHandler* input);
	virtual void onSendPacket(C_Packet* packet);
	virtual void onPlayerTick(C_Player* plr);
	virtual const char* getRawModuleName();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual bool isHoldMode();
	virtual void onDisable();
	virtual void onEnable();
	Flight();

	std::vector<C_MovePlayerPacket> movePacket1;
	std::vector<PlayerAuthInputPacket> authPacket1;
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};