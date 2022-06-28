#pragma once
#include "Module.h"

class FlyFO : public IModule {
private:
	bool doViewBobbing = true;
	bool addPacket = true;
	bool haltMovement = true;
	bool rots = false;
	float speed = 1.f;
	float speedEffective = 0;
	int antiDetectTime = 0;
	float maxDrop = 0.4;

public:
	SettingEnum antiDetectMode;

	FlyFO();
	~FlyFO();

	const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
