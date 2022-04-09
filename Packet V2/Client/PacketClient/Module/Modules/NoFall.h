#pragma once

#include "Module.h"

class NoFall : public IModule {
public:
	int dist = 3;
	
	std::string name = "Killaura";
	C_MoveInputHandler* inputHandler = nullptr;
	SettingEnum mode = this;

	NoFall();
	virtual const char* getModuleName();
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};