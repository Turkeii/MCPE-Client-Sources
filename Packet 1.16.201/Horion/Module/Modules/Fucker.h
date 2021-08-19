#pragma once
#include "Module.h"
#include "../ModuleManager.h"

class Fucker : public IModule {
private:
	int range = 5;
	bool beds = false;
	bool dOre = false;
	bool rOre = false;
	bool eOre = false;
	bool air = false;
	bool dirt = false;
	bool iron = false;
	bool gold = false;
	bool sandstone = false;
	bool stone = false;
	bool grass = false;
	bool eggs = false;
	bool cakes = false;
	bool treasures = false;
	bool chests = false;
	bool barrels = false;
	bool carrots = false;

public:
	Fucker();
	~Fucker();

	// Inherited via IModule
	virtual void onDisable() override;
	virtual const char* getModuleName() override;
	virtual void onTick(C_GameMode* gm) override;
};