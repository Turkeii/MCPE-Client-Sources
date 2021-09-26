#pragma once
#include "Module.h"
class Criticals : public IModule {
private:
	bool tester = false;

public:
	Criticals();
	~Criticals();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(C_Packet* packet) override;
	virtual void onTick(C_GameMode* gm) override;
};
