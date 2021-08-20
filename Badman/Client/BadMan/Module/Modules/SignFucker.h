#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class SignFucker : public IModule {
private:
	int range = 5;

public:
	SignFucker();
	~SignFucker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
