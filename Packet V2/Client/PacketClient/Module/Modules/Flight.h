#pragma once
#include "Module.h"
class Flight : public IModule {
private:
	bool speedWasEnabled = false;
	bool viewBobbing = true;
	bool damage = false;
	bool boost = false;
public:
	float effectiveValue = 0.f;
	float value = 0.f;
	float duration = 1.f;
	float speed = 1.f;

		std::string name = "Flight";
		C_MovePlayerPacket* jetpack = nullptr;
		SettingEnum mode = this;

	Flight();
	~Flight();

	// Inherited via IModule
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual bool isFlashMode() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onMove(C_MoveInputHandler* input) override;

	std::vector<C_MovePlayerPacket> movePacket1;
	std::vector<PlayerAuthInputPacket> authPacket1;
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};