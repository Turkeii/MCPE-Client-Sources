#pragma once
#include "Module.h"

class LockHealth : public IModule
{
public:
	LockHealth();
	~LockHealth() {}

	virtual const char* getModuleName() override;

	int health;

	void onTick(C_GameMode*) override;
};


