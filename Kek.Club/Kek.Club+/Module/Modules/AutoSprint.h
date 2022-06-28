#pragma once
#include "Module.h"
class AutoSprint : public IModule {
private:
	bool alldirections = false;
	bool keyPressed = false;
	SettingEnum SprintMode;

public:
	AutoSprint();
	~AutoSprint();

	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
	virtual const char* getModName() override;
};
