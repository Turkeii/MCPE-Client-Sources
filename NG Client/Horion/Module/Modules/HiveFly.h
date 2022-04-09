#pragma once
#include "Module.h"
class HiveFly : public IModule {
public:
	HiveFly();
	~HiveFly();

	int counter = 0;
	bool clip = false;
	float clipHeight = 2.f;
	int counter69 = 0;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onLevelRender();
	virtual void onSendPacket(C_Packet* packet);
};