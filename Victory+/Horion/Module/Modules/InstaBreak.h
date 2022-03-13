#pragma once
#include "Module.h"

class InstaBreak : public IModule {
public:
    int delay = 5;
    bool instant = false;
	bool packet = false;
	bool haste = false;

	SettingEnum Modes;

	InstaBreak();
	~InstaBreak();
	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};
