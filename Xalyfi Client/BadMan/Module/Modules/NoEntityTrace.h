#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class NoEntityTrace : public IModule {
private:
	bool noWeapon = true;

public:
	NoEntityTrace();
	~NoEntityTrace();

	bool allMobs = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};
