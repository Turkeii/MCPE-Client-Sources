#pragma once
#include "Module.h"

class AutoAnvil : public IModule {
public:
	bool tryAutoTrap(vec3_t AutoTrap);
	bool airplace = true;
	bool blockSwap = false;
	int blocks_per_tick = 1;
	bool Spoof();
	bool spoofC = false;
	bool slientSwitch = false;
	bool anvil = false;
	bool none = false;
	bool obsidian = true;
	SettingEnum mode;

	AutoAnvil();
	~AutoAnvil();

	int range = 7;
	bool onClick = false;

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
