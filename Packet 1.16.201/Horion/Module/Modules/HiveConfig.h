#pragma once

#include "Module.h"

class HiveConfig : public IModule {
private:
	bool autoPlay = false;
	bool ccconfigMode = false;
	bool hiveconfigMode = false;

public:
	HiveConfig();
	virtual const char* getModuleName();
	virtual void onDisable() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
};