#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class HackerDetect : public IModule {
private:
	int counter = 0;

public:
	HackerDetect();
	~HackerDetect();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* packet) override;
};