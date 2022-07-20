#pragma once
#include "Module.h"
class AntiHunger : public IModule {
public:
	AntiHunger();
	~AntiHunger();

	bool ground = true;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
