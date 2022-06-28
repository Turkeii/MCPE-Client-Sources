#pragma once
#include "Module.h"
class Notifications : public IModule {
public:
	SettingEnum notification;
	bool java = false;
	bool time = false;
	bool box = false;
	Notifications();
	~Notifications();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
