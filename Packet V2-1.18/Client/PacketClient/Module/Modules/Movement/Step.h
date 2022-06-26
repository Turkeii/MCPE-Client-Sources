#pragma once
#include "../../ModuleManager.h"
#include "../Module.h"

class Step : public IModule {
private:
	float height = 1.5f;
public:
	bool reverse = false;

	std::string name = "Step";
	SettingEnum mode = this;

	virtual void onMove(C_MoveInputHandler* input);
	virtual const char* getRawModuleName();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	virtual void onDisable();
	Step();
};