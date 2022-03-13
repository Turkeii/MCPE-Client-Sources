#pragma once
#include "Module.h"

class AntiCrystal : public IModule {
private:

	bool Auto = false;
	bool Bypass = false;
	float timer = 0.f;
	float range = 5.f;

public:

		int distance = 0.f;

	bool crystal = false; 
	AntiCrystal();
	~AntiCrystal();

	SettingEnum mode;

	virtual const char* getModuleName() override;
	virtual const char* getModName() override;

	virtual void onSendPacket(C_Packet* packet) override;
	virtual const char* getRawModuleName() override;
};
