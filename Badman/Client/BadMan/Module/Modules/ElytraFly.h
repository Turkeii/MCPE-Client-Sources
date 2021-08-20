#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class ElytraFly : public IModule {
public:
	float speed = 1.f;
	bool flying = false;

	ElytraFly();
	~ElytraFly();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onMove(C_MoveInputHandler* input) override;
};
