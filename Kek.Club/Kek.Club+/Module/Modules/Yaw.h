#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class Yaw : public IModule {
public:
	SettingEnum Direction;
	Yaw();
	~Yaw();
	virtual const char* getModuleName() override;
	virtual void onPlayerTick(C_Player* plr);
	
};