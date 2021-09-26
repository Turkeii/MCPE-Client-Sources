#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class HiveNuker : public IModule {
private:
	int range = 5;

public:
	HiveNuker();
	~HiveNuker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
