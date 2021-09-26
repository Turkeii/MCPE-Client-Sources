#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class Fucker : public IModule {
private:
	int range = 5;
	bool rot = true;
	bool beds = false;
	bool eggs = false;
	bool cakes = false;
	bool treasures = false;
	bool chests = true;
	bool barrels = false;
	bool redstone = true;
	bool diamond = true;
	bool emerald = true;

public:
	Fucker();
	~Fucker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};