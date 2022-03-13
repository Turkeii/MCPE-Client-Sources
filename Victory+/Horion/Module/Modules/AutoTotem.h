#pragma once
#include "Module.h"

class AutoTotem : public IModule {
private:
 
	bool totem = false; 
	bool shield = false;

public:
	AutoTotem();
	~AutoTotem();

	SettingEnum type;

	virtual const char* getModName() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
