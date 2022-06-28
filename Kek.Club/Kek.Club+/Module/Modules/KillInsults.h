#pragma once

#include "Module.h"

class KillInsults : public IModule {
public:
	bool killed = false;

	KillInsults();

	SettingEnum mode = this;

	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onEnable();
};