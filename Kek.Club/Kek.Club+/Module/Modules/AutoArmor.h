#pragma once
#include "Module.h"
class AutoArmor : public IModule {
public:
	AutoArmor();
	~AutoArmor();
	SettingEnum Mode;
	bool setArmor = false;

	virtual void craftingScreenController_tick(C_CraftingScreenController* c);
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getModuleName() override;
};