#pragma once
#include "Module.h"

class Disabler : public IModule {
public:
	bool netherDis = false;
	bool mineDis = false;
	bool ccDis = false;
	bool minevilleDis = false;

	Disabler();
	~Disabler();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onSendPacket(C_Packet* packet) override;
};