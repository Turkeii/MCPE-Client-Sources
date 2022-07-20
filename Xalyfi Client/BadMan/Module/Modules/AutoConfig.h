#pragma once
#include "Module.h"
#include "..\..\Config\ConfigManager.h"

class AutoConfig : public IModule {
public:
	int place = 0;
	bool AutoSave = false;

	AutoConfig();
	~AutoConfig();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
#pragma once
