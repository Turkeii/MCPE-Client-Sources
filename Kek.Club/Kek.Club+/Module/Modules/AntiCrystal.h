#pragma once
#include "Module.h"

class AntiCrystal : public IModule {
private:
	bool Bypass = false;
	bool endzone = false;
	float timer = 0.f;
	float Height = 0.1f;

public:
	bool sink = true;

	AntiCrystal();
	~AntiCrystal();

	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onSendPacket(C_Packet* packet) override;
};
