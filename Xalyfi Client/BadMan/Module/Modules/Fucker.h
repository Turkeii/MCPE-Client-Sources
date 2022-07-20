

#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Fucker : public IModule {
private:
	int range = 5;
	int hotbar = 5;
	bool beds = true;
	bool eggs = true;
	bool cakes = true;
	bool treasures = true;
	bool chests = false;
	bool barrels = false;
	bool redstone = true;
	bool emerald = false;
	bool diamond = false;
	bool health = false;
	bool swith23 = false;

public:
	Fucker();
	~Fucker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};
