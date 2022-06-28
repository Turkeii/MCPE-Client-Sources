#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class EChestFarmer : public IModule {
private:
	int range = 5;
	bool autopickaxe = true;
public:
	EChestFarmer();
	~EChestFarmer();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
	virtual void onEnable() override;
};
