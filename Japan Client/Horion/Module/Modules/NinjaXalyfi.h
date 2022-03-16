#pragma once
#include "Module.h"

class AntiCrystal : public IModule {
private:
	bool Auto = false;
	bool Bypass = false;
	float timer = 0.f;
	float range = 5.f;

public:
	float distance = 0.f;

	bool crystal = false;
	AntiCrystal();
	~AntiCrystal();

	SettingEnum mode;

	virtual const char* getModuleName() override;
	//virtual const char* getModName() override;
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};
#pragma once
