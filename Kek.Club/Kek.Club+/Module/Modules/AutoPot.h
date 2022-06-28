#pragma once
#include "../ModuleManager.h"
#include "Module.h"
class AutoPot : public IModule {
private:
	bool hold;
public:
	int range = 6;
	int delay = 0;
	int Odel = 0;
	int health = 3;
	AutoPot();
	~AutoPot();

	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
