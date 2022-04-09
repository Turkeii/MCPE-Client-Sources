#pragma once
#include "Module.h"

class Phase : public IModule {
private: 
	bool vertMode = false;

public:
	Phase();
	~Phase();

	std::string name = "Phase";
	SettingEnum mode = this;

	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};