#pragma once
#include "Module.h"
class SpinAtack : public IModule {
public:
	int amount = 1;
	SpinAtack();
	~SpinAtack();

private:
	virtual const char* getModuleName() override;
	//virtual void onEnable() override;
	void onTick(C_GameMode* gm);
};