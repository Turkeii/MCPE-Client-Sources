#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class NoFall : public IModule {
private:
	bool smart = true;
	bool groundy = false;
	int counter = 1;
	bool elytra = true;
	int distance = 3;
	bool motion = false;
	float glideMod = 0.f;
	float glideModEffective = 0;

public:
	float range = 3;
	NoFall();
	~NoFall();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	static void LoopbackPacketSender_sendToServer(C_LoopbackPacketSender* a, C_Packet* packet);
	void onTick(C_GameMode* gm);
};