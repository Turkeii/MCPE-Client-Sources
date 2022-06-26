#pragma once
#include "../../ModuleManager.h"
#include "../../Utils/DrawUtils.h"
#include "../Module.h"

class Ambience : public IModule {
public:
	float time = 1.f;

	std::string name = ("Ambience");
	SettingEnum weather = this;

	virtual const char* getRawModuleName();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm);
	Ambience();
};